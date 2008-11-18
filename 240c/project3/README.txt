Please use our makefile.  The priority_queue doesn't function correctly 
using g++ on the solaris machines.  It acts as a simple queue instead.  I 
don't know why, except that the libraries on the solaris machines are not 
the gnu libraries, so perhaps there is a difference there.  
If you want to see it in action, compile using our makefile (which uses CC, 
sun's c++ compiler) and run the program.  Make note of the arrival 
times vs. the airing times of the stories.  Then do the same after 
compiling with g++.  
You'll notice that with g++ almost every story airs within two or three 
minutes of its arrival.  Also, the average wait time for the stories is an 
order of magnitude smaller.  
It's worth mentioning that the priority_queue functions correctly using 
g++ on the computers in our group which all use the gnu c++ libraries.  
It's just the combination of g++ and the non-gnu libraries provided by Sun 
that causes this problem.
