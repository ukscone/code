/*Jonathan Plona
 *CS240c Project 1
 *April 15, 2008
 *
 *This class represents a doubly-linked list.  It stores the data in
 *instances of the dnode class.  It provides methods for adding to
 *and removing from either end of the list, and for adding to and 
 *removing from specific points in the list.  This is accomplished 
 *through the use of a bi-directional external iterator contained in 
 *the dnode_iterator class.
 */

#ifndef DLIST_H
#define DLIST_H

#include "dnode.h"
#include "dnode_iterator.h"

template <class T>
class dlist
{
    public:
        typedef dnode_iterator<T> iterator;
        
        //Constructors
        dlist() : head(NULL), tail(NULL), size(0) {}
        ~dlist() {while(!is_empty()) remove_head();}
        dlist(const dlist<T>& other) : head(NULL), tail(NULL), size(0) {
            for(iterator it = other.begin(); it != other.end(); ++it) {     //Copy list over.
                insert_tail(T(*it));
            }
        }
        //Assignment operator
        dlist<T>& operator=(const dlist<T>& other) {
            if(this == &other) return;                  //Check for self-assignment.
            while(!is_empty) remove_head();             //Clear list.
            for(iterator it = other.begin(); it != other.end(); ++it) {     //Copy list over.
                insert_tail(T(*it));
            }
        }            
        
        bool is_empty() {return size == 0;}
        int get_size() const {return size;}
        //Remove node specified.
        void remove_at(iterator& it) {
            if(it.current == NULL) return;                      //Check for valid node.
            else if(it.current == head) remove_head();          //Check for head and tail.
            else if(it.current == tail) remove_tail();                      
            else {
                it.current->get_prev()->set_next(it.current->get_next());
                it.current->get_next()->set_prev(it.current->get_prev());
                delete it.current;
                --size;
            }
        }
        //Insert data after the node specified.
        void insert_after(iterator& it, T data) {
            if(it.current == tail) {insert_tail(data);} //Check if we're inserting at the end of the list.
            else {
                dnode<T>* newNode = new dnode<T>(data, it.current->get_next(), it.current);
                newNode->get_prev()->set_next(newNode);
                newNode->get_next()->set_prev(newNode);
                ++size;
            }
        }
        //Insert data before the node specified.
        void insert_before(iterator& it, T data) {
            if(it.current == head) {insert_head(data);} //Check if we're inserting at the beginning of the list.
            else {
                dnode<T>* newNode = new dnode<T>(data, it.current, it.current->get_prev());
                newNode->get_prev()->set_next(newNode);
                newNode->get_next()->set_prev(newNode);
                ++size;
            }
        }
        //Insert data at the head of the list.
        void insert_head(T data) {
            dnode<T>* newNode = new dnode<T>(data, head, NULL);
            if(is_empty()) {     //Check for empty list.
                head = newNode;
                tail = head;
            } else {
                head->set_prev(newNode);
                head = newNode;   
            }   
            ++size;     
        }
        //Insert data at the tail of the list.
        void insert_tail(T data) {
            dnode<T>* newNode = new dnode<T>(data, NULL, tail);
            if(is_empty()) {     //Check for empty list.
                tail = newNode;
                head = tail;
            } else {
                tail->set_next(newNode);
                tail = newNode;
            }
            ++size;
        }
        //Remove the node at the head of the list.
        void remove_head() {
            if(is_empty()) return;         //Check for empty list.
            dnode<T>* temp = head;
            head = head->get_next();
            if(size == 1) tail = NULL;     //Check for list with one element.
            else head->set_prev(NULL);
            delete temp;
            --size;
        }
        //Remove the node at the tail of the list.
        void remove_tail() {
            if(is_empty()) return;         //Check for empty list.
            dnode<T>* temp = tail;
            tail = tail->get_prev();
            if(size == 1) head = NULL;
            else tail->set_next(NULL);
            delete temp;
            --size;
        }
        //Iterator Hooks
        iterator begin() const {return iterator(head);}        //Points to head.
        iterator rbegin() const {return iterator(tail);}       //Points to tail.
        iterator end() const {return iterator(NULL);}          //Points to one past tail.
        iterator rend() const {return iterator(NULL);}         //Points to one before head.
        
    private:
        dnode<T>* head;
        dnode<T>* tail;
        int size;
};

#endif
