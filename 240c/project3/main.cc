//*************************************************
// Group B
// Names:  Kevin Janowiecki, Jonathan Plona,
//         Wiley Hill, Neil Kreinbrink
// Class:  CS240C, Professor Dolan
// File:   This is the main.
// Date:   Wednesday May 14, 2008
//*************************************************

#include <iostream>
#include <string>
#include <fstream>
#include <sysexits.h>
#include "simulation.h"
using namespace std;

void usage();
void output(string dead_stories, ostream& fouts);

int main(int argc, char* argv[]) {
  //Check for the proper number of arguments.
  if((argc < 2)||(argc > 3)) {usage(); return EX_USAGE;}
  
  //Retrieve the arguments.
  int minutes = atof(argv[1])*60;
  string s = "";
  if(argc == 3) s = argv[2];
  
  //Make sure the arguments are valid.
  if(minutes <= 0) {usage(); return EX_USAGE;}
  if(argc == 3 && s != "-c") {usage(); return EX_USAGE;}
  
  ofstream fout("log/stories.log");
  ofstream deadfout("log/dead_stories.log");
  
  //Run the simulation and output the dead stories to a file.
  Simulation sim(cout, fout);
  bool censored = sim.run(minutes);       		
  output(sim.get_dead_stories(), deadfout);
  
  //Check for censored stories.
  if(s == "-c" && censored) cout << "Censor Exception encountered" << endl;
  
  fout.close();
  deadfout.close();
  return 0;
}

void usage() { //Print a usage message to the console.
    cout << "Invalid command-line arguments." << endl;
    cout << "Correct usage: main HOURS_TO_RUN [-c]" << endl;
    cout << "The [-c] option will warn the user if a story was censored." << endl;
}

void output(string dead_stories, ostream& fouts) { //Output dead stories to a file.
  fouts << dead_stories;
}
