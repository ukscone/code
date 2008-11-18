#!/usr/bin/python

import os, sys
import pygame
from random import choice
from pygame.locals import *

from blocks import Block
from shape import *
from wall import Wall
from linechecker import LineChecker


class TetrisMain:
    """Main Tetris class. Initializes and creates the game."""
    def __init__(self, blocksize=25):
        """Initialize"""
        pygame.mixer.pre_init(44100, -16, 2, 1024)
        pygame.init()
        
        self.width = 16*blocksize
        self.height = 21*blocksize
        self.blocksize = blocksize
        
        self.linechecker = LineChecker(self.blocksize)
        
        # LShape, RShape, SShape, ZShape, TShape, SquareShape, StraightShape
        self.shapes = [LShape, RShape, SShape, TShape, SquareShape, StraightShape, ZShape]
        
        self.screen = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption("Keltris")
        
        self.background = pygame.Surface.convert(pygame.image.load(os.path.join("data", "background.png")))
        
        self.update_time = 0
        self.paused = False
        
    def LoadSprites(self):
        """Loads stuff?"""
        self.shape = choice(self.shapes)(self.blocksize, choice(xrange(4)))
        self.bottom = pygame.sprite.RenderUpdates()
        self.sides = pygame.sprite.Group()
        self.barriers = pygame.sprite.Group()
        self.top = Wall(14*self.blocksize, self.blocksize, (self.blocksize, -self.blocksize))
        
        self.bottom.add(Wall(14*self.blocksize, self.blocksize, (self.blocksize, 20*self.blocksize), "bottom.png"))
        #left side, then right side
        self.sides.add(Wall(self.blocksize, 21*self.blocksize, (0, 0), "sides.png"))
        self.sides.add(Wall(self.blocksize, 21*self.blocksize, (15*self.blocksize, 0), "sides.png"))
        self.barriers.add(self.sides)
        self.barriers.add(self.bottom)
        self.barriers.add(self.top)
        
    def LoadMusic(self):
        pygame.mixer.music.load(os.path.join("data", "tetris3_tetoroika.ogg"))
        pygame.mixer.music.play(-1)
    
    def MainLoop(self):
        """Main loop of the game."""
        self.new_game()
        while 1:
            if self.paused:
                event = pygame.event.wait()
                while not (event.type == KEYDOWN and event.key in [K_p, K_PAUSE]):
                    event = pygame.event.wait()
                self.handle_event(event)
            for event in pygame.event.get():
                self.handle_event(event)
            
            if pygame.time.get_ticks() > self.update_time:
                self.shape.move(K_DOWN, self.barriers)
                self.update_time = pygame.time.get_ticks() + 1000
                
            if pygame.sprite.groupcollide(self.shape, self.bottom, False, False):
                self.shape.backup()
                self.bottom.add(self.shape)
                self.barriers.add(self.bottom)
                self.linechecker.checklines(self.bottom)
                updates = self.shape.draw(self.screen)
                pygame.display.update(updates)
                self.shape = choice(self.shapes)(self.blocksize, choice(xrange(4)))
                
            if pygame.sprite.spritecollide(self.top, self.bottom, False):
                self.end_game()
               
            updates = self.shape.draw(self.screen) + self.bottom.draw(self.screen)
            pygame.display.update(updates)
            pygame.time.wait(5)
            self.shape.clear(self.screen, self.background)
            self.bottom.clear(self.screen, self.background) 
            
    def handle_event(self, event):
        """Handles game events"""
        if event.type == pygame.QUIT:
            sys.exit()
        elif event.type == KEYDOWN:
            if event.key in [K_ESCAPE, K_q]:
                sys.exit()
            elif event.key in [K_p, K_PAUSE]:
                if self.paused:
                    self.unpause_game()
                else:
                    self.pause_game()
            else:
                self.shape.move(event.key, self.barriers)
                
    def pause_game(self):
        pygame.mixer.music.fadeout(300)
        self.paused = True
        
    def unpause_game(self):
        pygame.mixer.music.play(-1)
        self.paused = False
        self.update_time = pygame.time.get_ticks() + 1000
            
    def end_game(self):
        self.new_game()
        
    def new_game(self):
        """Starts a new game"""
        self.LoadSprites()
        self.LoadMusic()
        self.screen.blit(self.background, self.background.get_rect())
        for sprite in self.sides:
            self.screen.blit(sprite.image, sprite.rect)
        pygame.display.update()
            
                
if __name__ == "__main__":
    MainWindow = TetrisMain()
    MainWindow.MainLoop()
