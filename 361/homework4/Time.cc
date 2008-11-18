#include "Time.h"

Time::Time(const string &time_str) throw(int){
  if (strptime(time_str.c_str(),"%Y-%m-%d%t%X",&time_it)==NULL) throw 1;  
  the_time = mktime(&time_it);
}

bool operator > (const Time &x1, const Time &x2) {
  return (difftime(x1.the_time,x2.the_time) > 0);
}
bool operator < (const Time &x1, const Time &x2) {
  return (difftime(x1.the_time,x2.the_time) < 0);
}
bool operator == (const Time &x1, const Time &x2) {
  return (difftime(x1.the_time,x2.the_time) == 0);
}
