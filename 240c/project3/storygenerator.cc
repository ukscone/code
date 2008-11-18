//*****************************************************
// Group B
// Names:  Kevin Janowiecki, Jonathan Plona,
//         Wiley Hill, Neil Kreinbrink
// Class:  CS240C, Professor Dolan
// File:   This is the "storygenerator.cc" file.  This
//         file contains the implementation for the 
//		   StoryGenerator class.
// Date:   Wednesday May 14, 2008
//*****************************************************

#include "storygenerator.h"
using namespace std;

StoryGenerator::StoryGenerator() {
	//Initialize headline patterns.
    string pats[] = {"nv", "nvn", "npn", "anv", "nvpn", "anvn", "anpn", "nvan",
                      "npan", "anvpn", "nvpan", "anvan", "anpan", "anvpan"};
    patterns = vector<string>(pats, pats + sizeof(pats) / sizeof(string));
    srand(time(NULL));
}

News_story StoryGenerator::next() {
    News_story story;
	int priority = 0;
    string headline = "";
    string pattern = patterns[rand() % patterns.size()];

    //Iterate through characters in the pattern string.
    for(unsigned int i = 0; i < pattern.size(); ++i) {
        char ch = pattern[i];
        vecpair* part_of_speech;
       	//Fetch the appropriate part of speech.
        switch (ch) {
            case 'n':  part_of_speech = &nouns;          break;
            case 'v':  part_of_speech = &verbs;          break;
            case 'p':  part_of_speech = &prepositions;   break;
            case 'a':  part_of_speech = &adjectives;     break;
            default:  assert(false);//Illegal pattern
        }
        //Get a word and its priority.
        int x = rand() % part_of_speech->size();
        headline += (*part_of_speech)[x].first + ' ';
        priority += (*part_of_speech)[x].second;
    }

    //Check for an llegal headline, otherwise return the story.
    if(is_explicit(headline)) throw pr0nexception();
    story.set_headline(headline);
    story.set_priority(priority);
    story.set_length(rand() % 3 + 1);
    return story;
}

void StoryGenerator::open(const char* nfile, const char* vfile,
                     const char* pfile, const char* afile) {
    load(nouns, nfile);
    load(verbs, vfile);
    load(prepositions, pfile);
    load(adjectives, afile);
}
void StoryGenerator::load(vecpair& vec, const char* f) {
	//Load information from a file into a vecpair.
    string word, priority;
    ifstream fin(f);
    while(getline(fin, word) && getline(fin, priority)) {
        vec.push_back(pair<string, int>(word, atoi(priority.c_str())));
    }
    fin.close();
}

bool StoryGenerator::is_explicit(std::string headline) {
	//Check for three occurences of the letter x in a headline.
    int xcount = 0;
    for(unsigned int i = 0; i < headline.size(); ++i) {
        if(headline[i] == 'x') ++xcount;
    }
    if(xcount > 2) return true;
    return false;        
}
