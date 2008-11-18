CCC = g++
CXXFLAGS = -g -Wall
LDFLAGS = -g -Wall -lcurses

OBJECTS = main.o reversi.o game.o board.o gamenet.o

reversi: $(OBJECTS)
	$(CCC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o reversi
main.o: main.cc reversi.h
reversi.o: reversi.h game.h board.h 
gamenet.o: gamenet.h
game.o: game.h gamenet.h
board.o: board.h

clean:
	rm -f *.o
	
install: clean
	mv reversi /usr/bin/reversi
