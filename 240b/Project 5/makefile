admintest: main.o administrator.o salariedemployee.o employee.o
	g++ -g -Wall main.o administrator.o salariedemployee.o employee.o -o admintest
	
test: test.o administrator.o salariedemployee.o employee.o
	g++ -g -Wall test.o administrator.o salariedemployee.o employee.o -o test

test.o: test.cpp
	g++ -g -Wall -c test.cpp -o test.o
	
main.o: main.cc
	g++ -g -Wall -c main.cc -o main.o

administrator.o: administrator.cc
	g++ -g -Wall -c administrator.cc -o administrator.o
	
salariedemployee.o: salariedemployee.cc
	g++ -g -Wall -c salariedemployee.cc -o salariedemployee.o
	
employee.o: employee.cc
	g++ -g -Wall -c employee.cc -o employee.o
