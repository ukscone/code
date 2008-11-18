#include "node.h"

CartList::CartList()
{
    head = NULL;
    maxtabs = 3;
}

CartList::~CartList()
{
    //Delete each node
    if(head != NULL) {
        Node* temp = head;
        Node* current = head->next;
        
        while(current != NULL) {
            delete temp;
            temp = current;
            current = current->next;
        }
        delete temp;
    }
}

void CartList::add(string item, double price)
{
    update_tabs(item);
    
    //Insert item at head of list
    Node* newitem = new Node;
    newitem->item = item;
    newitem->price = price;
    
    newitem->next = head;
    head = newitem;    
}

double CartList::remove(string item)
{
    //If the list is empty, return item not found
    if(head == NULL) return -1.0;
    //If the item is at the beginning of the list, remove it
    if(head->item == item) {
        double price = head->price;
        head = head->next;
        return price;
    }
        
    //Find the node before the item
    Node* before = head;
    while(before->next != NULL && before->next->item != item) {
        before = before->next;
    }
    
    //If the item is in the list, remove it
    if(before->next != NULL) {
        Node* temp = before->next;
        double price = temp->price;
        before->next = temp->next;
        delete temp;
        return price;
    }
    return -1.0;
}

string CartList::to_string()
{
    stringstream strm(stringstream::in|stringstream::out);
    
    Node* current = head;
    
    //Format the list into two columns, Item and Price.
    strm << "Item" + tabstring("Item") + "Price\n\n";
    while(current != NULL) {
        strm << current->item;
        strm << tabstring(current->item);
        strm << "$";
        strm << current->price;
        if(int(current->price) == current->price) strm << ".00";
        else if (int(current->price*100)%10 == 0) strm << '0';
        
        strm << "\n";
        current = current->next;
    }
    strm << "\n\n";
    
    return strm.str();
}

void CartList::update_tabs(string item)
{
    //Calculate the number of tabs between the two columns
    int tabs = int(floor(item.length()/8.0)) + 2;
    if(tabs > maxtabs) maxtabs = tabs;
}

string CartList::tabstring(string str)
{
    //Calculate the number of tabs between the string and the next column
    string tabs = "";
    for(int i = 0; i < maxtabs - int(floor(str.length()/8.0)); ++i) {
        tabs += "\t";
    }
    return tabs;
}
