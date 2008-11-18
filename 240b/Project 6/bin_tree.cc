#include "bin_tree.h"
using namespace std;

Tree::Tree()
{
	left = NULL;
	right = NULL;
	data = "";
}

bool Tree::contains(string item)
{
	int comparison = item.compare(data);
	
	if(comparison == 0) return true;
	if(comparison < 0) {
		if(left == NULL) return false;
		return left->contains(item);
	}
	if(comparison > 0) {
		if(right == NULL) return false;
		return right->contains(item);
	}
	//We never get here
	return false;
}

void Tree::insert(string item)
{
	if(!data.compare("")) {
		data = item;
		return;
	}
	int comparison = item.compare(data);
	if(comparison < 0) {
		if(left == NULL) left = new Tree;
		left->insert(item);
	}
	if(comparison > 0) {
		if(right == NULL) right = new Tree;
		right->insert(item);
	}
}

void Tree::postprint()
{
	if(left != NULL) left->postprint();
	if(right != NULL) right->postprint();
	cout << data << endl;
}

void Tree::preprint()
{
	cout << data << endl;
	if(left != NULL) left->preprint();
	if(right != NULL) right->preprint();
}

void Tree::inprint()
{
	if(left != NULL) left->inprint();
	cout << data << endl;
	if(right != NULL) right->inprint();
}
