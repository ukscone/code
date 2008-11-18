/*Jonathan Plona
 *CS240c Project 1
 *April 15, 2008
 *
 *This class implements a bi-directional external iterator for the dlist class.
 *It has two methods, next() and prev(), which respectively advance and regress 
 *the iterator.  It supports the comparison operators == and !=, the dereferencing
 *operator *, and the increment and decrement operators which are equivalent to
 *next() and prev().
 */


#ifndef DNODE_ITERATOR_H
#define DNODE_ITERATOR_H

#include "dnode.h"

template <class T>  //Forward declaration of dlist class.
class dlist;

template <class T>
class dnode_iterator
{
    public:
        friend class dlist<T>;  //Allow the dlist class to access private member current.
    
        dnode_iterator(dnode<T>* cur = NULL) : current(cur) {}
        
        dnode_iterator<T>& next() { //Go forward one node.
            if(current != NULL) current = current->get_next();
            return *this;
        }
        dnode_iterator<T>& prev() { //Go back one node.
            if(current != NULL) current = current->get_prev(); 
            return *this;
        }
        
        //Operators
        T operator*() const {
            if(current != NULL) return current->get_data();
            else return T(); //If iterator is invalid, return empty node.
        }
        bool operator!=(const dnode_iterator& other) const {return current != other.current;}
        bool operator==(const dnode_iterator& other) const {return current == other.current;}
        dnode_iterator& operator++() {next(); return *this;}
        dnode_iterator& operator++(int) {next(); return *this;}
        dnode_iterator& operator--() {prev(); return *this;}
        dnode_iterator& operator--(int) {prev(); return *this;}
    private:
        dnode<T>* current;
};

#endif
