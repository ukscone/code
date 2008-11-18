reverse: main.o node.o
	g++ -Wall main.o node.o -o reverse
main.o: main.cc node.h
	g++ -Wall -c main.cc -o main.o
node.o: node.cc node.h
	g++ -Wall -c node.cc -o node.o
clean: 
	rm -f *.o
cleanall:
	rm -f reverse *.o
