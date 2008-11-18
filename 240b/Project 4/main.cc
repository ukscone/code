#include <iostream>
#include <string>
#include <stdlib.h>

#include "shopping_cart.h"

using namespace std;

void get_input(string& input);
//IN: String
//OUT: Assigns input to string

void handle_input(string& input);
//IN: String containing input
//OUT: Handles the input

void display_help();
//IN: 
//OUT: Displays help

ShoppingCart* cart;

int main()
{
    cart = new ShoppingCart;
    
    //Enter input loop.
    system("clear");    
    string input;
    while(input != "Quit" && input != "quit" && input != "q") {
        get_input(input);
    }
    system("clear");
    
    delete cart;
    return 0;
}

void get_input(string& input)
{
    //Prompt user for input
    cout << "Please enter a command, or type 'help' for a list of commands: ";
    cin >> input;
    
    handle_input(input);
}

void handle_input(string& input)
{
    string item;
    double price;
    bool found;
    
    /*
     *Handle input
     */
    //Display help
    if(input == "help") {
        display_help();
    }
    //Add item
    else if(input == "add") {
        cin >> item >> price;
        cart->add_item(item, price);
    }
    //Remove item
    else if(input == "remove") {
        cin >> item;
        found = cart->remove_item(item);
        if(!found) cout << "Item " << item << " was not found." << endl;
    }
    //List cart contents
    else if(input == "list") {
        system("clear");
        cout << "\n";
        cout << cart->to_string() << endl;
    }
    //If user enters quit, do nothing
    else if(input == "quit" || input == "Quit" || input == "q") {
    }
    //Warn user of unrecognized command
    else {
        cout << "\nUnrecognized command, please try again." << endl;
    }
}

void display_help() 
{
    system("clear");
    
    cout << "Command\t    Description" << endl << endl;
    
    cout << "help\t    Displays this help screen." << endl << endl;
    
    cout << "add\t    Adds an item to the cart." << endl << endl;
    cout << "\t        Usage: add item price" << endl;
    cout << "\t               where item is a string and price is a double." << endl << endl << endl;
    
    cout << "remove\t    Removes an item from the cart." << endl << endl;
    cout << "\t        Usage: remove item" << endl;
    cout << "\t               where item is a string." << endl << endl << endl;
    
    cout << "list\t    Displays the contents of the cart." << endl << endl;
    
    cout << "quit\t    Exits the program." << endl << endl;
    
}
