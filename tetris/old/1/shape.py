from random import random

import pygame
from pygame.locals import *

from blocks import Block

class Shape(pygame.sprite.RenderUpdates):
    """Base class for all tetris pieces"""
    def __init__(self, blocksize):
        pygame.sprite.RenderUpdates.__init__(self)
        self.blocksize = blocksize
        
        self.orientation = 0
        
    def move(self, key, barriers):
        """Handles movement keys (arrow keys + space)"""
        if key in [K_RIGHT, K_LEFT]:
            temp = self.copy()
            self._do_move(temp, key)
            if not pygame.sprite.groupcollide(temp, barriers, False, False):
                self._do_move(self, key)
        elif key == K_DOWN:
            self._do_move(self, K_DOWN)
        elif key == K_UP:
            self.rotate(barriers)
        elif key == K_SPACE:
            while not pygame.sprite.groupcollide(self, barriers, False, False):
                self._do_move(self, K_DOWN)
            self.backup()
            
    def backup(self):
        for block in self:
            block.rect.move_ip(0, -25)
            
    def _do_move(self,group, key):
        for block in group:
            block.move(key)
            
    def copy(self):
        """Makes a copy of self for location and collision purposes"""
        temp = StraightShape(self.blocksize, self.orientation)
        for (boxtemp, boxself) in zip(temp, self):
            boxtemp.rect.topleft = boxself.rect.topleft
        return temp
        
    def rotate(self, barriers):
        self._do_rotate(self)
            
        if pygame.sprite.groupcollide(self, barriers, False, False):
            self._do_rotate(self)
            self._do_rotate(self)
            self._do_rotate(self)
            
    def _do_rotate(self, group):
        """Subclasses should override this method for piece-specific rotation"""
        pass

class StraightShape(Shape):
    """Straight piece"""
    def __init__(self, blocksize, orientation):
        Shape.__init__(self, blocksize)
        
        #Shape starts horizontal
        self.axis = Block(blocksize, '0', (blocksize*7, blocksize))
        self.add(Block(blocksize, '0', (blocksize*6, blocksize)))
        self.add(self.axis)
        self.add(Block(blocksize, '0', (blocksize*8, blocksize)))
        self.add(Block(blocksize, '0', (blocksize*9, blocksize)))
        
        #If desired orientation is vertical, rotate
        if orientation % 2:
            self._do_rotate(self)
            
    def _do_rotate(self, group):
        axis = self.axis.rect.topleft
        vertical = self.orientation % 2
        self.orientation += 1
        self.orientation %= 4
        
        for box in group:
            loc = box.rect.topleft
            y = loc[1] - axis[1]
            x = loc[0] - axis[0]
            diff = y - x
            box.rect.move_ip(diff, -diff)
            
            
class SquareShape(Shape):
    """Square Piece"""
    def __init__(self, blocksize, orientation):
        Shape.__init__(self, blocksize)
        
        self.add(Block(blocksize, '1', (blocksize*7, 0)))
        self.add(Block(blocksize, '1', (blocksize*8, 0)))
        self.add(Block(blocksize, '1', (blocksize*7, blocksize)))
        self.add(Block(blocksize, '1', (blocksize*8, blocksize)))


class ZShape(Shape):
    """Z Piece"""
    def __init__(self, blocksize, orientation):
        Shape.__init__(self, blocksize)
        
        #Shape starts horizontal
        self.axis = Block(blocksize, '2', (blocksize*8, blocksize))
        self.add(Block(blocksize, '2', (blocksize*7, 0)))
        self.add(Block(blocksize, '2', (blocksize*8, 0)))
        self.add(self.axis)
        self.add(Block(blocksize, '2', (blocksize*9, blocksize)))
        
        #If desired orientation is vertical, rotate
        if orientation % 2:
            self._do_rotate(self)
        
    def _do_rotate(self, group):
        axis = self.axis.rect.topleft
        vertical = self.orientation % 2
        self.orientation += 1
        self.orientation %= 4
        
        if vertical:
            new_locations = [(axis[0] - group.blocksize, axis[1] - group.blocksize),
                             (axis[0], axis[1] - group.blocksize),
                             (axis[0] + group.blocksize, axis[1])]
        else:
            new_locations = [(axis[0] - group.blocksize, axis[1] + group.blocksize),
                             (axis[0] - group.blocksize, axis[1]), 
                             (axis[0], axis[1] - group.blocksize)]
        
        for (box, location) in zip([sprite for sprite in group if sprite.rect.topleft != axis], new_locations):
            box.rect.topleft = location
        
        
class SShape(Shape):
    """S Piece"""
    def __init__(self, blocksize, orientation):
        Shape.__init__(self, blocksize)
        
        #shape starts horizontal
        self.axis = Block(blocksize, '3', (blocksize*8, blocksize))
        self.add(Block(blocksize, '3', (blocksize*7, blocksize)))
        self.add(self.axis)
        self.add(Block(blocksize, '3', (blocksize*8, 0)))
        self.add(Block(blocksize, '3', (blocksize*9, 0)))
        
        #If desired orientation is vertical, rotate
        if orientation % 2:
            self._do_rotate(self)
        
    def _do_rotate(self, group):
        axis = self.axis.rect.topleft
        vertical = self.orientation % 2
        self.orientation += 1
        self.orientation %= 4
        
        if vertical:
            new_locations = [(axis[0] - group.blocksize, axis[1]),
                             (axis[0], axis[1] - group.blocksize),
                             (axis[0] + group.blocksize, axis[1] - group.blocksize)]
        else:
            new_locations = [(axis[0], axis[1] - group.blocksize),
                             (axis[0] + group.blocksize, axis[1]), 
                             (axis[0] + group.blocksize, axis[1] + group.blocksize)]
        
        for (box, location) in zip([sprite for sprite in group if sprite.rect.topleft != axis], new_locations):
            box.rect.topleft = location
        
class LShape(Shape):
    """L Piece"""
    def __init__(self, blocksize, orientation):
        Shape.__init__(self, blocksize)
        
        self.orientation = 3
        
        #Starts off in an 'L' orientation
        self.axis = Block(blocksize, '4', (blocksize*7, blocksize))
        self.add(Block(blocksize, '4', (blocksize*7, 0)))
        self.add(self.axis)
        self.add(Block(blocksize, '4', (blocksize*7, blocksize*2)))
        self.add(Block(blocksize, '4', (blocksize*8, blocksize*2)))
        
        while self.orientation != orientation:
            self._do_rotate(self)
        
    def _do_rotate(self, group):
        axis = self.axis.rect.topleft
        orientation = self.orientation
        self.orientation += 1
        self.orientation %= 4
        
        if orientation == 0:
            new_locations = [(axis[0] - group.blocksize, axis[1] - group.blocksize),
                             (axis[0], axis[1] - group.blocksize),
                             (axis[0], axis[1] + group.blocksize)]
        elif orientation == 1:
            new_locations = [(axis[0] - group.blocksize, axis[1] + group.blocksize),
                             (axis[0] - group.blocksize, axis[1]),
                             (axis[0] + group.blocksize, axis[1])]
        elif orientation == 2:
            new_locations = [(axis[0], axis[1] - group.blocksize),
                              (axis[0], axis[1] + group.blocksize),
                              (axis[0] + group.blocksize, axis[1] + group.blocksize)]
        elif orientation == 3:
            new_locations = [(axis[0] - group.blocksize, axis[1]),
                             (axis[0] + group.blocksize, axis[1]),
                             (axis[0] + group.blocksize, axis[1] - group.blocksize)]
                             
        for (box, location) in zip([sprite for sprite in group if sprite.rect.topleft != axis], new_locations):
            box.rect.topleft = location
        

class RShape(Shape):
    """_| Piece"""
    def __init__(self, blocksize, orientation):
        Shape.__init__(self, blocksize)
        
        self.orientation = 3
        
        self.axis = Block(blocksize, '5', (blocksize*8, blocksize))
        self.add(Block(blocksize, '5', (blocksize*8, 0)))
        self.add(self.axis)
        self.add(Block(blocksize, '5', (blocksize*8, blocksize*2)))
        self.add(Block(blocksize, '5', (blocksize*7, blocksize*2)))
        
        while self.orientation != orientation:
            self._do_rotate(self)
        
    def _do_rotate(self, group):
        axis = self.axis.rect.topleft
        orientation = self.orientation
        self.orientation += 1
        self.orientation %= 4
        
        if orientation == 0:
            new_locations = [(axis[0] + group.blocksize, axis[1] - group.blocksize),
                             (axis[0], axis[1] - group.blocksize),
                             (axis[0], axis[1] + group.blocksize)]
        elif orientation == 1:
            new_locations = [(axis[0] - group.blocksize, axis[1] - group.blocksize),
                             (axis[0] - group.blocksize, axis[1]),
                             (axis[0] + group.blocksize, axis[1])]
        elif orientation == 2:
            new_locations = [(axis[0], axis[1] - group.blocksize),
                              (axis[0], axis[1] + group.blocksize),
                              (axis[0] - group.blocksize, axis[1] + group.blocksize)]
        elif orientation == 3:
            new_locations = [(axis[0] - group.blocksize, axis[1]),
                             (axis[0] + group.blocksize, axis[1]),
                             (axis[0] + group.blocksize, axis[1] + group.blocksize)]
                             
        for (box, location) in zip([sprite for sprite in group if sprite.rect.topleft != axis], new_locations):
            box.rect.topleft = location
        
class TShape(Shape):
    """T Piece"""
    def __init__(self, blocksize, orientation):
        Shape.__init__(self, blocksize)
        
        self.axis = Block(blocksize, '6', (blocksize*7, blocksize))
        
        self.add(Block(blocksize, '6', (blocksize*6, blocksize)))
        self.add(self.axis)
        self.add(Block(blocksize, '6', (blocksize*8, blocksize)))
        self.add(Block(blocksize, '6', (blocksize*7, blocksize*2)))
        
        while self.orientation != orientation:
            self._do_rotate(self)
            
    def _do_rotate(self, group):
        axis = self.axis.rect.topleft
        orientation = self.orientation
        self.orientation += 1
        self.orientation %= 4
        
        if orientation == 0:
            new_locations = [(axis[0] + group.blocksize, axis[1]),
                             (axis[0], axis[1] - group.blocksize),
                             (axis[0], axis[1] + group.blocksize)]
        elif orientation == 1:
            new_locations = [(axis[0] - group.blocksize, axis[1]),
                             (axis[0], axis[1] - group.blocksize),
                             (axis[0] + group.blocksize, axis[1])]
        elif orientation == 2:
            new_locations = [(axis[0], axis[1] - group.blocksize),
                              (axis[0], axis[1] + group.blocksize),
                              (axis[0] - group.blocksize, axis[1])]
        elif orientation == 3:
            new_locations = [(axis[0] - group.blocksize, axis[1]),
                             (axis[0] + group.blocksize, axis[1]),
                             (axis[0], axis[1] + group.blocksize)]
                             
        for (box, location) in zip([sprite for sprite in group if sprite.rect.topleft != axis], new_locations):
            box.rect.topleft = location
        
