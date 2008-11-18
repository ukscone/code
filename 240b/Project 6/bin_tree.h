#ifndef TREE_H
#define TREE_H

#include <string>
#include <iostream>

using namespace std;

class Tree
{
	public:
		Tree();
		bool contains(string item);
		void insert(string item);
		void postprint();
		void preprint();
		void inprint();
	private:
		string data;
		Tree* left;
		Tree* right;
};

#endif
