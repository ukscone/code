//*****************************************************
// Group B
// Names: Kevin Janowiecki, Jonathan Plona, Wiley Hill,
//        Neil Kreinbrink
// Class: CS240C, Professor Dolan
// File:  This is the "news_story.h" file. This file
//        contains the class declaration of the News_story
//        class. The News_story class is used by the
//        StoryGenerator class to create new random news
//        stories.
// Date:  Wednesday, May 14, 2008
//******************************************************

#ifndef NEWS_STORY_H
#define NEWS_STORY_H

#include <string>
#include <iostream>

class News_story{
 public:
  //Default Constructor
  News_story();

  //Operators
  friend std::ostream& operator<<(std::ostream&, const News_story&);
  bool operator<(const News_story& news) const;

  //Accessor Functions
  std::string get_headline() {return headline;}
  int get_length() {return length_of_story;}
  int get_arrival_time() {return arrival_time;}
  int get_priority() {return priority_level;}
  int get_airing_time() {return airing_time;}

  //Mutator Functions
  void set_headline(std::string new_head) {headline = new_head;}
  void set_length(int new_length) {length_of_story = new_length;}
  void set_arrival_time(int arr_time) {arrival_time = arr_time;}
  void set_priority(int new_priority) {priority_level = new_priority;}
  void set_airing_time(int air_time) {airing_time = air_time;}

 private:
  std::string headline;
  int length_of_story, arrival_time, priority_level, airing_time;
};

#endif
