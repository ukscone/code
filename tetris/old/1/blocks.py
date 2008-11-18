import os
import pygame
from pygame.locals import *

class Block(pygame.sprite.Sprite):
    """Represents a block"""
    images = {}
    def __init__(self, size, color, position):
        """initializes a block.  Takes a size in pixels, a color (R, G, B), and a position (x, y)"""
        self.size = size
        
        self.filename = "block" + color + ".png"
    
        #initialize pygame sprite
        pygame.sprite.Sprite.__init__(self)
    
        #Only load one copy of each image
        if not self.filename in Block.images:
            Block.images[self.filename] = pygame.Surface.convert_alpha(pygame.image.load(os.path.join("data", "block" + color + ".png")))
        
        #image
        self.image = Block.images[self.filename]
        
        #location
        self.rect = self.image.get_rect()
        self.rect.topleft = position
        
    def move(self, key):
        #number of pixels to move
        y = 0
        x = 0
        
        if key == K_RIGHT:
            x = self.size
        elif key == K_LEFT:
            x = -self.size
        elif key == K_UP:
            y = -self.size
        elif key == K_DOWN:
            y = self.size
        self.rect.move_ip(x, y)
