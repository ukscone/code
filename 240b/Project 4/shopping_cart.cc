#include "shopping_cart.h"

ShoppingCart::ShoppingCart()
{    
    items = new CartList();
    total_price = 0;
}

ShoppingCart::~ShoppingCart()
{
    delete items;
}

void ShoppingCart::add_item(string item, double price)
{
    //Add item and update total price
    items->add(item, price);
    total_price += price;
}

bool ShoppingCart::remove_item(string item)
{
    //Remove item and update total price
    double price = items->remove(item);
    if(price != -1.0) {
        total_price -= price;
        return true;
    }
    return false;
}

double ShoppingCart::get_total_price()
{
    return total_price;
}

string ShoppingCart::to_string()
{
    return items->to_string();
}
