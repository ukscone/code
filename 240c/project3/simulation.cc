//*************************************************
// Group B
// Names:  Kevin Janowiecki, Jonathan Plona,
//         Wiley Hill, Neil Kreinbrink
// Class:  CS240C, Professor Dolan
// File:   This is the "simulation.cc" file.  This
//         file contains the implementation for the 
//		   Simulation class.
// Date:   Wednesday May 14, 2008
//*************************************************

#include "simulation.h"

// Constructor
Simulation::Simulation(std::ostream& term_outs, std::ostream& file_outs) {
  term_out = &term_outs;
  file_out = &file_outs;
  story_gen.open("data/noun2.txt", "data/verb.txt", "data/preps.txt", "data/adjectives.txt");
  dead_stories = "";
  srand(time(NULL));
}

// Accessor for dead stories
std::string Simulation::get_dead_stories() {return dead_stories;}

// Main run program
bool Simulation::run(int minutes) {
  int story_count = 0; 
  int tot_wait_time = 0; 			//Total wait time for all stories aired.
  bool censor_exception = false; 	//True if the censor exception is ever true.
  bool caught = false; 				//True if the censor exception is true this minute.
  int time_left = 0; 				//Time left in current story
  
  for(int time = 0; time < minutes; ++time) { 
    if(rand() < .75*RAND_MAX){ //Check for new story
	  News_story temp;
	  try {
	    temp = story_gen.next();
	  }
	  catch(pr0nexception){
	    censor_exception = true;
	    caught = true;
	  }
	  if(!caught){ //If exception isn't triggered
	    temp.set_arrival_time(time);
	    stories.push(temp);
	  }
    }
      
    if(stories.empty()){ //If there aren't any stories in the queue
	  std::cout << "No story during this minute\n" << std::endl;
    }
    else {
	  if(time_left < 1){ //If no story is currently playing, play new story.
	    News_story to_show = stories.top(); stories.pop();
	    
	    to_show.set_airing_time(time);
  	    time_left = to_show.get_length();
	    tot_wait_time += to_show.get_airing_time() - to_show.get_arrival_time();
	    ++story_count;
	    
	    (*term_out) << to_show << std::endl;  //Output to the console
	    (*file_out) << to_show << std::endl;  //Output to the log file
	  }
    }
    caught = false; //Reset caught variable
    --time_left; 	//Run one minute of the current story
  }
  
  //Output final information to console and log file
  (*term_out) << "Total number of stories broadcast: " << story_count << std::endl;
  (*file_out) << "Total number of stories broadcast: " << story_count << std::endl;
  (*term_out) << "Average wait time in queue: " << (int)((1.0*tot_wait_time)/story_count*60) << " seconds" <<  std::endl;
  (*file_out) << "Average wait time in queue: " << (int)((1.0*tot_wait_time)/story_count*60) << " seconds" <<  std::endl;
  
  //Append all stories that haven't been aired to dead_stories.
  std::ostringstream os;
  while(!stories.empty()){
    os << stories.top() << '\n';
    stories.pop();
  }
  dead_stories = os.str();
  
  //Check for censor exception
  if(censor_exception) return true; 
  return false;
}
