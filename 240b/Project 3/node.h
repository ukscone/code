#include <vector>

struct Node {
    int data;
    Node* link;
};

void reverse_list_recursive(Node*& head);
//IN: A Pointer to the head of a linked list.
//OUT: The linked list is reversed.

void reverse_list_ptrs(Node*& head);
//IN: A Pointer to the head of a linked list.
//OUT: The linked list is reversed.
