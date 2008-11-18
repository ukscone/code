//*****************************************************
// Group B
// Names: Kevin Janowiecki, Jonathan Plona, Wiley Hill,
//        Neil Kreinbrink
// Class: CS240C, Professor Dolan
// File:  This is the exception that gets raised when
//		  a story violates the censorship rule.
// Date:  Wednesday, May 14, 2008
//******************************************************

#ifndef PR0N_EXCEPTION_H
#define PR0N_EXCEPTION_H
#include <exception>

class pr0nexception : public std::exception
{
    virtual const char* what() const throw()
    {
        return "Story cannot be run due to explicit content.";
    }
};
#endif
