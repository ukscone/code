//*************************************************
// Group B
// Names:  Kevin Janowiecki, Jonathan Plona,
//         Wiley Hill, Neil Kreinbrink
// Class:  CS240C, Professor Dolan
// File:   This is the "simulation.h" file.  This
//         file contains the class declaration for
//         the class Simulation. The simulation
//         class is used to run the bulk of the
//         program which entails generating stories,
//         etc.
// Date:   Wednesday May 14, 2008
//*************************************************

#ifndef SIMULATION_H
#define SIMULATION_H

#include <ostream>
#include <fstream>
#include <queue>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "storygenerator.h"
#include "news_story.h"
#include "pr0nexception.h"

class Simulation {
  
 public:    
  //Constructor
  Simulation(std::ostream& term_outs, std::ostream& file_outs);
  
  //Function to return stories that didn't make the air
  std::string get_dead_stories();
  
  //Run function which returns true if censor exception is caught
  bool run(int minutes);
  
 private:
  std::ostream* term_out;
  std::ostream* file_out;
  StoryGenerator story_gen;
  std::priority_queue<News_story> stories;
  std::string dead_stories;    
};

#endif
