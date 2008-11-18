//*************************************************
// Group B
// Names:  Kevin Janowiecki, Jonathan Plona,
//         Wiley Hill, Neil Kreinbrink
// Class:  CS240C, Professor Dolan
// File:   This is the "storygenerator.h" file.
//		   This class loads word and priority 
//		   information from data files, and then 
//		   generates random stories.
// Date:   Wednesday May 14, 2008
//*************************************************

#ifndef STORY_GENERATOR_H
#define STORY_GENERATOR_H

#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include "news_story.h"
#include "pr0nexception.h"

class StoryGenerator {

 public:
    StoryGenerator();
    
    //Return a random story.
    News_story next();
    
    //Initialize generator with wordlists.
    void open(const char* nfile, const char* vfile,
                     const char* pfile, const char* afile);
    
 private:
 	//A vecpair is a vector of pairs of strings and ints.
    typedef std::vector< std::pair<std::string, int> > vecpair;
    vecpair nouns;
    vecpair verbs;
    vecpair prepositions;
    vecpair adjectives;
    std::vector<std::string> patterns;
    //Load information from a file into a vecpair.
    void load(vecpair& vec, const char* f);
    //Check for 3 occurences of the letter x in a headline.
    bool is_explicit(std::string headline);
};
#endif
