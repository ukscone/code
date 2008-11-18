#include "node.h"

void reverse_list_recursive(Node*& head)
{
	//Base Case: List of size 0 or 1
	if(head == NULL || head->link == NULL) {
		return;
	}
	
	//Find the second to last item
    Node* second_to_last = head;
    while(second_to_last->link->link != NULL) {
    	second_to_last = second_to_last->link;
    }
    
    //Insert last element at beginning
    second_to_last->link->link = head;
    
    //Update head pointer
    head = second_to_last->link;
    
    //Remove last element from the end
    second_to_last->link = NULL;
    
    //Recurse
    reverse_list_recursive(head->link);
}

void reverse_list_ptrs(Node*& head)
{
	//If list is size 0 or 1 it is already reversed
	if(head == NULL || head->link == NULL) return;
	
	//Pointers to keep track of everything
	Node *headl, *headr, *swap;
	
	//Split the list into three groups: a left side(already reversed), one element in the middle, and a right side(not yet reversed).
	headl = head;
	swap = headl->link;
	headr = swap->link;
	
	//Swap
	headl-> link = NULL;
	while(headr != NULL) {
		swap->link = headl;
		headl = swap;
		swap = headr;
		headr = headr->link;
	}
	swap-> link = headl;
	head = swap;
}
