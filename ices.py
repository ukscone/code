"""
TODO:
Detect all removable media.
Detect changes in folders
"""


from string import *
import sys
import os
import random
import fnmatch



def ices_init():
	global elist, elist1, playlist, playlist1, metadata
	
	temp = makelist('/home/jonathan/Music')

	elist = temp[0]
	elist1 = elist[:]
	error = temp[1]

	temp2 = makelist('/media/disk/Yarr!/Music')
	
	playlist = temp2[0]
	playlist1 = playlist[:]
	error = temp2[1]

	return error
		

def ices_get_next():
	if os.path.exists('/media/disk/Yarr!/Music'):
		workinglist = playlist1
		steadylist = playlist
		meta = metadata
		if not workinglist:
			workinglist = steadylist[:]
		index = random.randrange(len(workinglist))
		selected = workinglist[index]
		meta = selected
		del workinglist[index]
		return selected
	elif os.path.exists('/home/jonathan/Music/'):
		workinglist = elist1
		steadylist = elist
		meta = metadata
		if not workinglist:
			workinglist = steadylist[:]
		index = random.randrange(len(workinglist))
		selected = workinglist[index]
		meta = selected
		del workinglist[index]
		return selected
	else:
		return ''
"""
def ices_get_metadata():
	return metadata 
"""

def makelist(path):
	error = 1
	try:
		if os.path.exists(path):
			for root, dirs, files in os.walk(path):
				songlist.append(f) for f in files if fnmatch.fnmatch(filename, '*.mp3')
						
	except:
		error = 0
	return songlist, error
