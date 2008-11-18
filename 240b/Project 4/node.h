#include <string>
#include <sstream>
#include <cmath>

using namespace std;

struct Node {
    string item;
    double price;
    Node* next;
};

class CartList
{
    public:
        CartList();
        ~CartList();
        
        void add(string item, double price);
        //IN: Item and price
        //OUT: Adds the item with the given price to the list.
        
        double remove(string item);
        //IN: Item
        //OUT: Removes item from the list and returns its price.  
        //     Returns -1.0 if the item is not found.
        
        string to_string();
        //IN:
        //OUT: Returns a tabular representation of the list.
        
    private:
        //Pointer to the head of the list
        Node* head;
        
        //These deal with spacing when the list is printed
        void update_tabs(string item);
        string tabstring(string str);
        int maxtabs;
};
