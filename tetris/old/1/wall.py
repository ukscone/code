import os
import pygame
from pygame.locals import *

class Wall(pygame.sprite.Sprite):
    """Long Sprite to act as a wall"""
    def __init__(self, width, height, position, filename=None):
        pygame.sprite.Sprite.__init__(self)
        
        if filename is not None:
            self.image = pygame.Surface.convert_alpha(pygame.image.load(os.path.join("data", filename)))
        else:
            self.image = pygame.Surface((width, height))
            self.image.fill((255, 255, 255))
        
        self.rect = self.image.get_rect()
        self.rect.topleft = position
