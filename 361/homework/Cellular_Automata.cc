#include <iostream>
#include "Cellular_Automata.h"
using namespace std;

Cellular_Automata::Cellular_Automata(list<pair<string,char> > & rules) throw (CA_exception) {
  list<pair<string,char> >::iterator p;

  bool ok = false;

  for(p = rules.begin(); p != rules.end(); ++p) {
  	if(p->first.length() == 3) myrules[p->first] = p->second;
  	else throw CA_exception("Invalid rule length");
  	if(p->first == "   " && p->second == ' ') ok = true;
  }
  
  if (!ok) {
    throw CA_exception("No default rule ");
  }
}


string Cellular_Automata::last_generation(string &initial, int num_of_generations) throw (CA_exception) {  string current_state = initial;
  string current_window, next_state;

  for (int i = 0; i < num_of_generations; i++) {
  	current_state = "  " + current_state + "  ";
    next_state = "";
    
    for(int i = 0; i <= current_state.length() - 3; ++i) {
    	current_window = current_state.substr(i, 3);
    	if(myrules.find(current_window) != myrules.end()) next_state += myrules[current_window];
    	else throw CA_exception("No rule for current window");
    }
    
    while(next_state[0] == ' ') next_state.erase(0, 1);
    while(next_state[next_state.length() - 1] == ' ') next_state.erase(next_state.length() - 1, 1);      
    
    current_state = next_state;
  }

  return current_state;
}

bool Cellular_Automata::appears(string &initial, int num_generations, string &target) throw (CA_exception) {
  if (initial.find(target) != string::npos) return true;  string current_state = initial;
  
  for(int i = 0; i < num_generations; ++i) {
  	current_state = last_generation(current_state, 1);
  	if (current_state.find(target) != string::npos) return true;
  }

  return false;
}

Cellular_Automata::~Cellular_Automata() {}
