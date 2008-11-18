//*****************************************************
// Group B
// Names: Kevin Janowiecki, Jonathan Plona, Wiley Hill,
//        Neil Kreinbrink
// Class: CS240C, Professor Dolan
// File:  This is the "news_story.cc" file. This file
//        contains the function implementations of the
//        News_story class. The News_story class is used
//        by the StoryGenerator class to create new 
//        random news stories.
// Date:  Wednesday, May 14, 2008
//******************************************************

#include "news_story.h"
#include <iostream>
#include <string>

//This is the default constructor
News_story::News_story(){
  headline = "No Headline";
  length_of_story = 0;
  arrival_time = 0;
  priority_level = 0;
  airing_time = 0;
}

//This is the overloaded insertion operator
//The story output looks like: 
//Headline 
//"tab" Arrival 
//"tab" Aired
std::ostream& operator<<(std::ostream& outs, const News_story& news){
  outs << news.headline << "\n\t" << "Story arrived at minute: " 
       << news.arrival_time << "\n\t" << "Story aired at minute: " 
       << news.airing_time << std::endl;
  return outs;
}

//This is the overloaded "less than" comparison operator
//It compares priority levels of two "News_story"s
bool News_story::operator<(const News_story& news) const{
  if(priority_level < news.priority_level) return true;
  return false;
}
