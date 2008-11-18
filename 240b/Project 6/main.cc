#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "bin_tree.h"
using namespace std;

bool main_menu();
bool main_choice(int choice);
void add();
void find();
void print_menu();
bool print_choice(int choice);

Tree tree;

int main()
{
    while(main_menu()) {};
    system("clear");

    return 0;
}

bool main_menu()
{
	int choice;
	system("clear");
	cout << "What would you like to do?" << endl
		 << endl
		 << "1. Add words" << endl
		 << "2. Find a word" << endl
		 << "3. Print words" << endl
		 << "4. Quit" << endl
		 << endl
		 << "Please enter your choice: ";
	while(!(cin >> choice)) {
		cout << "Invalid input, please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if(choice == 4) return false;
	while(!main_choice(choice)) {
		while(!(cin >> choice)) {
			cout << "Invalid choice, please try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}
	return true;
}

bool main_choice(int choice)
{
	switch(choice) {
		case 1:
			add();
			return true;
			break;
		case 2:
			find();
			return true;
			break;
		case 3:
			print_menu();
			return true;
			break;
		default:
			cout << "Invalid choice, please try again: ";
			return false;
			break;
	}
}

void add()
{
	vector<string> words;
	string word;
	
	cin.get();
	cout << endl << "Please enter a list of words to add: ";
	while(cin.peek() != '\n' && cin >> word) {
		words.push_back(word);
	}
	
	for(int x = 0; x < (int)words.size(); ++x) {
		tree.insert(words[x]);
	}
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void find()
{
	string word;
	string contains;
	cout << endl << "Please enter the word you wish to find: ";
	cin >> word;
	contains = tree.contains(word) ? "" : "not ";
	cout << endl
		 << word << " was " << contains << "found" << endl
		 << endl
		 << "Press Enter to continue: ";
	cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void print_menu()
{
	int choice;
	system("clear");
	cout << "What order would you like to print?" << endl
		 << endl
		 << "1. Prefix" << endl
		 << "2. Postfix" << endl
		 << "3. Infix" << endl
		 << endl
		 << "Please enter your choice (-1 to quit): ";
	while(!(cin >> choice) || !print_choice(choice)) {
	 	cout << "Invalid choice, please try again: ";
	 	cin.clear();
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

bool print_choice(int choice) 
{
	bool ret = false;
	switch(choice) {
		case -1:
			return true;
		case 1:
			system("clear");
			tree.preprint();
			ret = true;
			break;
		case 2:
			system("clear");
			tree.postprint();
			ret =  true;
			break;
		case 3:
			system("clear");
			tree.inprint();
			ret = true;
			break;
		default:
			cout << "Invalid choice, please try again: ";
			return false;
			break;
	}
	cout << endl
		 << "Press Enter to continue: ";
	cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	
	return ret;
}
