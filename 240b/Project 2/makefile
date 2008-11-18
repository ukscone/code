CC = g++
FILES = block_cipher.cc block_cipher.h encode.cc decode.cc makefile in_text
EOBJECTS = block_cipher.o encode.o
DOBJECTS = block_cipher.o decode.o
CFLAGS = -Wall -c
LFLAGS = -Wall
DEBUG = -g

all: decode encode

decode: $(DOBJECTS)
	$(CC) $(LFLAGS) $(DEBUG) $(DOBJECTS) -o decode
encode: $(EOBJECTS)
	$(CC) $(LFLAGS) $(DEBUG) $(EOBJECTS) -o encode
block_cipher.o: block_cipher.cc block_cipher.h
	$(CC) $(CFLAGS) $(DEBUG) block_cipher.cc
encode.o: encode.cc block_cipher.h
	$(CC) $(CFLAGS) $(DEBUG) encode.cc
decode.o: decode.cc block_cipher.h
	$(CC) $(CFLAGS) $(DEBUG) decode.cc

clean:
	rm -f *.o encoded decoded
cleanall: clean
	rm -f core out_text decoded_text decode encode
tar:
	tar -cvzf blockCipher.tar.gz $(FILES)
