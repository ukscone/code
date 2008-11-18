import os
import shutil

mp3Map = {  "title" :   (3, 33),
			"artist"  : (33, 63),
			"album" :   (63, 93),
			"year" :    (93, 97),
			"comment" : (97, 126),
			"genre" :   (127, 128)}

def getTags(filename, tagMap):
	try:
		f = open(filename)
		try:
			f.seek(-128, 2)
			tagdata = f.read(128)
		finally:
			f.close()
	except IOError:
		pass
		
	tagseq = [(tag, tagdata[start:end].replace("\00", "").strip()) for tag, (start, end) in tagMap.items()]
	tagdict = dict(tagseq)
	return tagdict

def setTags(filename, tags = {}, tagMap = mp3Map):
    try:
        f = open(filename, 'r+')
        try:
            f.seek(-125, 2)
            f.write('balls       ')
        finally:
            f.close()
    except IOError:
        pass
            
	
if __name__ == "__main__":
	filenm = "4Him - The Basics Of Life.mp3"
	setTags(filenm)
	filedict = getTags(filenm, mp3Map)
	for key in filedict:
		print key, " : ", filedict[key]
