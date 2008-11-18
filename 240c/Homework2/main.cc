#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>

#include "House.h"
#include "DogHouse.h"
#include "BeaverDam.h"
#include "DeathStar.h"
#include "WaffleHouse.h"
#include "PolarBearIgloo.h"

using namespace std;

bool main_menu();
bool main_choice(int choice);
void add_menu();
bool add_choice(int choice);
void display_houses();
void load_houses();
void save_houses();

list<House*> houses;

int main()
{
    load_houses();
    while(main_menu()) {};
    save_houses();
    system("clear");
    return 0;
}

bool main_menu()
{
	int choice;
	system("clear");
	cout << "What would you like to do?" << endl
		 << endl
		 << "1. Add a house" << endl
		 << "2. List houses" << endl
		 << "3. Quit" << endl
		 << endl
		 << "Please enter your choice: ";
	while(!(cin >> choice)) {
		cout << "Invalid input, please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if(choice == 3) return false;
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
			add_menu();
			return true;
		case 2:
			display_houses();
			return true;
		default:
			cout << "Invalid choice, please try again: ";
			return false;
	}
}

void add_menu()
{
	int choice;
	system("clear");
	cout << "What type of house would you like to add?" << endl
		 << endl
		 << "1. Dog House" << endl
		 << "2. Waffle House" << endl
		 << "3. Beaver Dam" << endl
		 << "4. Death Star" << endl
		 << "5. Polar Bear Igloo" << endl
		 << "6. Go back" << endl
		 << endl
		 << "Please enter your choice: ";
	while(!((cin >> choice) && add_choice(choice))) {
	 	cout << "Invalid choice, please try again: ";
	 	cin.clear();
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

bool add_choice(int choice) 
{
    House* temp;
    switch(choice) {
        case 1: {
            temp = new DogHouse;
            break;
        }
        case 2: {
            temp = new WaffleHouse;
            break;
        }
        case 3: {
            temp = new BeaverDam;
            break;
        }
        case 4: {
            temp = new DeathStar;
            break;
        }
        case 5: {
            temp = new PolarBearIgloo;
            break;
        }
        case 6: {
            return true;
        }
        default: {
            cout << "Invalid choice, please try again: ";
			return false;
	    }
	}
	cin.get();
    temp->read(cin, cout);
    houses.push_back(temp);
    return true;
}

void display_houses()
{
    cin.get();
    for(list<House*>::iterator it = houses.begin(); it != houses.end(); ++it) {
        system("clear");    
        (*it)->print(cout);
        cout << endl
    		 << "Press Enter to continue: ";
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


void load_houses() 
{
    string input;
    ifstream fin("houses.dat");
    House* temp;
    
    while(fin >> input) {
        if(input == "dog") {
            temp = new DogHouse;
        }
        else if(input == "waffle"){
            temp = new WaffleHouse;
        }
        else if(input == "beaver") {
            temp = new BeaverDam;
        }
        else if(input == "sith") {
            temp = new DeathStar;
            fin >> input;
        }
        else if(input == "polar") {
            temp = new PolarBearIgloo;
            fin >> input;
        }
        fin.get();
    	getline(fin, input);
    	cout << input;
        temp->unserialize(input);
        houses.push_back(temp);   
    }
}
void save_houses() 
{ 
    ofstream fout("houses.dat");
    for(list<House*>::iterator it = houses.begin(); it != houses.end(); ++it) {
        fout << (*it)->serialize() << endl;
    }
}
