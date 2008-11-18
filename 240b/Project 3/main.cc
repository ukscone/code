#include <iostream>
#include <vector>
#include "node.h"

#define SIZE 1000

using namespace std;

bool compare(Node*& head, int original[]);

int main()
{
	//Pointer to the head of the list
    Node* head = NULL;
    
    int original[SIZE];
    
    //Create a list to test
    for(int x = SIZE - 1; x >= 0; --x) {
        Node* newnode = new Node;
        newnode->data = x;
        newnode->link = head;
        head = newnode;
        
        original[x] = x;
    }
    
    //Reverse the list (recursive method), then
	//Reverse the list again (three pointers method)
    reverse_list_recursive(head);
    reverse_list_ptrs(head);
    
    //Compare the twice-reversed list with the original values
	if(compare(head, original))		cout << "Success!" << endl;
	else 							cout << "Failure..." << endl;
    
    return 0;
}

bool compare(Node*& head, int original[])
{
	Node* current = head;
	for(int i = 0; i < SIZE; ++i) {
		if(original[i] != current->data) {
			return false;
		}
		current = current->link;
	}
	
	return true;
}
