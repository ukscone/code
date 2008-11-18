all:mst shortpath neg_cycle
mst:mst.o GraphAlgorithms.o routines.o
	g++ -g -o mst mst.o GraphAlgorithms.o routines.o
shortpath:shortpath.o GraphAlgorithms.o routines.o
	g++ -g -o shortpath shortpath.o GraphAlgorithms.o routines.o
neg_cycle:neg_cycle.o GraphAlgorithms.o routines.o
	g++ -g -o neg_cycle neg_cycle.o GraphAlgorithms.o routines.o
mst.o:mst.cc GraphAlgorithms.h 
	g++ -g -c mst.cc
shortpath.o:shortpath.cc GraphAlgorithms.h
	g++ -g -c shortpath.cc
neg_cycle.o:neg_cycle.cc GraphAlgorithms.h 
	g++ -g -c neg_cycle.cc
GraphAlgorithms.o:GraphAlgorithms.cc GraphAlgorithms.h
	g++ -g -c GraphAlgorithms.cc
routines.o:routines.cc
	g++ -g -c routines.cc
