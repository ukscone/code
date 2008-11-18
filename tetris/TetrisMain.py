#!/usr/bin/python

import os, sys
import pygame
from pygame.locals import *

from mainpanel import MainPanel
from musicmanager import MusicManager

import cProfile


class TetrisMain:
    """Main Tetris class. Initializes and creates the game."""
    def __init__(self, blocksize=25):
        """Initialize"""
        pygame.mixer.pre_init(44100, -16, 2, 1024)
        pygame.init()
        
        self.width = 21*blocksize
        self.height = 21*blocksize
        self.blocksize = blocksize
        
        self.screen = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption("Keltris")
        self.mainpanel = MainPanel(self.screen, self.blocksize)
        
        self.music = MusicManager()
        
        self.paused = True
        
        
    def LoadMusic(self):
        self.music.load()
        self.music.play()
    
    def MainLoop(self):
        """Main loop of the game."""
        self.mainpanel.new_game()
        self.new_game()
        while 1:
            if self.paused:
                event = pygame.event.wait()
                while not (event.type == KEYDOWN and event.key in [K_p, K_PAUSE]):
                    event = pygame.event.wait()
                self.handle_event(event)
                
            for event in pygame.event.get():
                self.handle_event(event)
                self.mainpanel.handle_event(event)
                self.music.handle_event(event)
            
            endgame = self.mainpanel.update(pygame.time.get_ticks())
            if endgame:
                self.end_game()
               
            updates = self.mainpanel.draw()
            self.screen.blit(self.mainpanel.image, self.mainpanel.rect)
            pygame.display.update(updates)
            pygame.time.wait(5)
            self.mainpanel.clear() 
            
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
                
    def pause_game(self):
        self.music.pause()
        self.paused = True
        
    def unpause_game(self):
        self.music.unpause()
        self.paused = False
        self.update_time = pygame.time.get_ticks() + 1000
            
    def end_game(self):
    	self.mainpanel.new_game()
        self.new_game()
        
    def new_game(self):
        """Starts a new game"""
        self.LoadMusic()
        self.screen.blit(self.mainpanel.image, self.mainpanel.rect)
        pygame.display.update()
            
                
if __name__ == "__main__":
    MainWindow = TetrisMain()
    cProfile.run("MainWindow.MainLoop()", filename="profile.cprof")
