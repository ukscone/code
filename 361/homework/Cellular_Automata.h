#include <list>
#include <algorithm>
#include <map>
#include <stdexcept>
#include <string>

using namespace std;

#ifndef CELLULAR_AUTOMATA
#define CELLULAR_AUTOMATA

class CA_exception:public invalid_argument {
 public:
  CA_exception(const char *x):invalid_argument(x){};
};


class Cellular_Automata {
 public:
  
  Cellular_Automata(list<pair<string,char> >& rules) throw (CA_exception);
  ~Cellular_Automata();



  string last_generation(string& initial, int num_of_generations) throw (CA_exception);

  bool appears(string& initial, int num_generations, string& target) throw (CA_exception);

 private:  
  map<string, char> myrules;
};

#endif
