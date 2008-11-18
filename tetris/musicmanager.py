import os, sys
import pygame.mixer as mixer
from pygame.locals import *

class MusicManager:
    def __init__(self):
        mixer.music.load(os.path.join("/home/jonathan/Music/The Blues Brothers/The Blues Brothers", "08 - Theme From Rawhide.ogg"))
        
        self.seek = 0
        
    def load(self):
        mixer.music.load(os.path.join("/home/jonathan/Music/The Blues Brothers/The Blues Brothers", "08 - Theme From Rawhide.ogg"))
        
    def play(self):
        mixer.music.play(-1)
        
    def pause(self):
        self.seek = mixer.music.get_pos()
        mixer.music.fadeout(300)
        
    def unpause(self):
        mixer.music.play(-1, self.seek)
        
        
    def mute(self, toggle=False):
        if toggle:
            if mixer.music.get_volume() == 0.0:
                mixer.music.set_volume(0.8)
            else:
                mixer.music.set_volume(0.0)
        else:
            mixer.music.set_volume(0.0)
        
    def handle_event(self, event):
    	if event.type == KEYDOWN and event.key == K_s:
    		self.mute(True)
