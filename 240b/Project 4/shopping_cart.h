#include <string>
#include <vector>
#include "node.h"

using namespace std;

class ShoppingCart
{
    public:
        ShoppingCart();
        ~ShoppingCart();
        
        double get_total_price();
        //IN:
        //OUT: Returns the total price
        
        void add_item(string item, double price);
        //IN: Item and price
        //OUT: Adds the item with the given price to the list. 
        
        bool remove_item(string item);
        //IN: Item
        //OUT: Removes item from the list and returns its price.  
        //     Returns false if the item is not found.
        
        string to_string();
        //IN:
        //OUT: Returns a tabular representation of the list.
        
    private:
        //Pointer to linked list containing the items in the cart
        CartList* items;
        
        //Total price of items in cart
        double total_price;
};
