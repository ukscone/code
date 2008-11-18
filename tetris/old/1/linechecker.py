import pygame
from pygame.locals import *

from wall import Wall

class LineChecker():
    """Checks a sprite group for completed horizontal lines"""
    def __init__(self, blocksize):
        self.blocksize = blocksize
        
        self.lines = [Wall(14*blocksize, blocksize, (blocksize, blocksize*x)) for x in xrange(20)]
        
    def checklines(self, bottom):
        for line in self.lines:
            if len(pygame.sprite.spritecollide(line, bottom, False)) == 14:
                self.remove_line(line, bottom)
                
    def remove_line(self, line, bottom):
        pygame.sprite.spritecollide(line, bottom, True)
        for box in bottom:
            if box.rect.topleft[1] < line.rect.topleft[1]:
                box.rect.move_ip(0, 25)
