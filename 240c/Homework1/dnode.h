/*Jonathan Plona
 *CS240c Project 1
 *April 15, 2008
 *
 *This class represents a node in a doubly-linked list.  It provides
 *setter and getter methods for the data, and both links.
 */
 
#ifndef DNODE_H
#define DNODE_H

template <class T>
class dnode
{
    public:
        dnode(T dat = 0, dnode* n = NULL, dnode* p = NULL) : data(dat), next(n), prev(p) {}
        
        //Setters
        void set_data(T dat) {data = dat;}
        void set_prev(dnode<T>* node) {prev = node;}
        void set_next(dnode<T>* node) {next = node;}
        //Getters
        T get_data() const {return data;}
        dnode<T>* get_next() const {return next;}
        dnode<T>* get_prev() const {return prev;}
    private:
        T data;
        dnode<T> *next, *prev;
};

#endif
