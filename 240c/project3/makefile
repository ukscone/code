#priority_queue doesn't function correctly using g++ on the solaris 
#machines, so I used CC (the solaris c++ compiler) instead.

CCC = CC
OBJECTS = main.o news_story.o simulation.o storygenerator.o

main: $(OBJECTS)
	$(CCC) $(OBJECTS) -o main

main.o: main.cc pr0nexception.h news_story.h simulation.h storygenerator.h
simulation.o:simulation.h storygenerator.h news_story.h pr0nexception.h
storygenerator.o:storygenerator.h news_story.h pr0nexception.h
news_story.o:news_story.h

clean:
	rm -f *.o
