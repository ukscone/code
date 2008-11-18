//******************************************************************************
// Author: 			Jonathan Plona
// Course: 			CS240C, Professor Dolan
// Description: 	This class provides the exception which is thrown in the 
//					event that there is a loss of network connection.
// Date:  			Tuesday, May 27, 2008
//******************************************************************************

#ifndef CONNECTION_EXCEPTION_H
#define CONNECTION_EXCEPTION_H
#include <exception>

class ConnectionException : public std::exception
{
    virtual const char* what() const throw()
    {
        return "The connection was lost.";
    }
};
#endif
