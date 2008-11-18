CCC = g++
CXXFLAGS = -Wall
LDFLAGS = -Wall

smake: Time.o  main.o
	g++ -Wall Time.o main.o -o smake
main.o: main.cc Time.h Node.h
Time.o: Time.h

clean:
	rm *.o
