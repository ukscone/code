#ifndef TIME_H
#define TIME_H

#include <ctime>
#include <iostream>

using namespace std;

class Time {
  public:
	Time() {the_time = 0;} //Ensure that files which do not exist yet are created.
	Time(const string &time_str) throw(int);
  
	friend bool operator > (const Time &x1, const Time &x2);
	friend bool operator < (const Time &x1, const Time &x2);
	friend bool operator == (const Time &x1, const Time &x2);

	void print() { 
		struct tm* l_time = localtime(&the_time);
		if(l_time == NULL) cerr << "The time is not set..." << endl;
  		else cout << "Time = " << asctime(l_time) << endl;
	}
  
	time_t raw_time() {return the_time;}
  
  private:
	time_t the_time;
	struct tm time_it;
};

#endif
