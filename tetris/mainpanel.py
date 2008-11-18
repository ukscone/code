import os, sys
import pygame
from random import choice
from pygame.locals import *

from blocks import Block
from shape import *
from wall import Wall
from linechecker import LineChecker

class MainPanel(pygame.sprite.Sprite):
    """Main Panel"""
    def __init__(self, screen, blocksize, position=(0, 0)):
        """Initialize main panel"""
        pygame.sprite.Sprite.__init__(self)
        
        self.blocksize = blocksize
        self.width = blocksize * 16
        self.height = blocksize * 21
        
        self.image = pygame.Surface((self.width, self.height))
        self.image.fill((255, 255, 255))
        
        self.rect = self.image.get_rect()
        self.rect.topleft = position
        
        # LShape, RShape, SShape, ZShape, TShape, SquareShape, StraightShape
        self.shapes = [LShape, RShape, SShape, TShape, SquareShape, StraightShape, ZShape]
        
        self.linechecker = LineChecker(self.blocksize)
        
        self.screen = screen
        self.background = pygame.Surface.convert(pygame.image.load(os.path.join("data", "background1.png")))
        
    def LoadSprites(self):
        """Loads stuff"""
        self.shape = choice(self.shapes)(self.blocksize, choice(xrange(4)))
        self.bottom = pygame.sprite.RenderUpdates()
        self.sides = pygame.sprite.Group()
        self.barriers = pygame.sprite.Group()
        self.top = Wall(14*self.blocksize, self.blocksize, (self.blocksize, -self.blocksize))
        self.bottom.add(Wall(14*self.blocksize, self.blocksize, (self.blocksize, 20*self.blocksize), "bottom.png"))
        self.sides.add(Wall(self.blocksize, 21*self.blocksize, (0, 0), "sides.png"))
        self.sides.add(Wall(self.blocksize, 21*self.blocksize, (15*self.blocksize, 0), "sides.png"))
        self.barriers.add(self.sides)
        self.barriers.add(self.bottom)
        self.barriers.add(self.top)
        
        self.image.blit(self.background, self.background.get_rect())
        for sprite in self.barriers:
            self.image.blit(sprite.image, sprite.rect)
        
    def update(self, time):
    	if time > self.update_time:
	        self.shape.move(K_DOWN, self.barriers)
	        if pygame.sprite.groupcollide(self.shape, self.bottom, False, False):
	            self.shape.backup()
	            self.bottom.add(self.shape)
	            self.barriers.add(self.shape)
	            lines = self.linechecker.checklines(self.bottom)
	            if lines:
		            updates = self.draw()
		            self.screen.blit(self.image, self.rect)
		            pygame.display.update(updates)
	            self.update_level(lines)
	            continue_game = self.next_shape()
	            if not continue_game:
	            	return True
	        self.update_time = time + self.update_length
        return False
        
    def update_level(self, lines=None):
    	if lines:
    		self.lines += lines
    	self.level = self.lines/10
    	self.update_length = 1000 - 100*self.level
        
    def handle_event(self, event):
    	if event.type == KEYDOWN:
    		self.move_shape(event)
    		
    def next_shape(self):
    	self.shape = choice(self.shapes)(self.blocksize, choice(xrange(4)))
    	if pygame.sprite.groupcollide(self.shape, self.bottom, False, False):
    		return False
    	return True
        
    def move_shape(self, event):
        self.shape.move(event.key, self.barriers)
        
    def draw(self):
        updates = self.shape.draw(self.image) + self.bottom.draw(self.image)
        return updates
        
    def clear(self):
        self.shape.clear(self.image, self.background)
        self.bottom.clear(self.image, self.background)
        
    def set_shape(self, shape):
        self.shape = shape
        
    def new_game(self):
    	self.LoadSprites()
    	self.update_time = 0
        self.update_length = 1000
        self.level = 0
        self.lines = 0
