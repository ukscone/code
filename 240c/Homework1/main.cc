/*Jonathan Plona
 *CS240c Project 1
 *April 15, 2008
 *
 *This is the main function for Project 1.  It does the following (copied from the assignment sheet):
 *(1) Read in the entire list of swatches.
 *(2) Make a copy of the list using either your copy constructor or your overloaded assignment operator.
 *(3) Remove the front, back and centermost swatch from the copy.
 *(4) Output the original list frontwards
 *(5) Output the copy frontwards.
 *(6) Output the original list backwards.
 *(7) Destroy the original list by alternating between removal of the first item and the last item.
 *(8) Output the copy backwards.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "dlist.h"
#include "swatches.h"

using namespace std;

void read_swatches(dlist<Swatch>& tehlist);
void print_swatches(const dlist<Swatch>& tehlist);
void print_reverse(const dlist<Swatch>& tehlist);
void destroy_list(dlist<Swatch>& tehlist);
void remove_middle(dlist<Swatch>& tehlist);
void insert_middle(dlist<Swatch>& tehlist, Swatch data);

int main()
{
    dlist<Swatch> swatches;
    read_swatches(swatches);                    //(1)
    dlist<Swatch> swatches_copy(swatches);      //(2)
    swatches_copy.remove_head();                //(3)
    swatches_copy.remove_tail();                //
    remove_middle(swatches_copy);               //
    print_swatches(swatches);                   //(4)
    print_swatches(swatches_copy);              //(5)
    print_reverse(swatches);                    //(6)
    destroy_list(swatches);                     //(7)
    print_reverse(swatches_copy);               //(8)
    
    return 0;
}
//Find the middle element of a list (or the one after the middle, for an even sized list) and remove it.
void remove_middle(dlist<Swatch>& tehlist) {
    int middle = tehlist.get_size()/2;
    dlist<Swatch>::iterator it = tehlist.begin();
    for(int x = 0; x < middle; ++it, ++x) {}
    tehlist.remove_at(it);
}
//Find the middle element of a list, and insert data after it.
void insert_middle(dlist<Swatch>& tehlist, Swatch data) {
    int middle = tehlist.get_size() - tehlist.get_size()/2;
    dlist<Swatch>::iterator it = tehlist.begin();
    for(int x = 0; x < middle - 1; ++it, ++x) {}
    tehlist.insert_after(it, data);
}
//Read in swatches from the file and add them to the list.
void read_swatches(dlist<Swatch>& tehlist) {
    ifstream infile("swatches.txt");
    Swatch temp;
    while(infile >> temp) {
        int red = temp.get_red(), green = temp.get_green(), blue = temp.get_blue();
        if(red >= green && red >= blue) tehlist.insert_head(temp);
        else if(green >= blue) tehlist.insert_tail(temp);
        else insert_middle(tehlist, temp);
    }
}
//Print the list in forward order.
void print_swatches(const dlist<Swatch>& tehlist) {
    for(dlist<Swatch>::iterator it = tehlist.begin(); it != tehlist.end(); ++it) {
        cout << *it << endl;
    }
}
//Print the list in reverse order.
void print_reverse(const dlist<Swatch>& tehlist) {
    for(dlist<Swatch>::iterator it = tehlist.rbegin(); it != tehlist.rend(); --it) {
        cout << *it << endl;
    }
}
//Alternate removing the head and tail of the list until the list is empty.
void destroy_list(dlist<Swatch>& tehlist) {
    void (dlist<Swatch>::*funcs[2])() = {&dlist<Swatch>::remove_head, &dlist<Swatch>::remove_tail};
    for(int x = 0; !tehlist.is_empty(); ++x) {
        (tehlist.*funcs[x%2])();
    }
}
