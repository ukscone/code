#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdlib>

#include "administrator.h"
using namespace std;

bool main_menu();
bool main_choice(int choice);
void add_menu();
bool add_choice(int choice);
void remove_menu();
bool remove_choice(int choice);
void edit_menu();
bool edit_choice(int choice);
void load();
void save();
void print_menu();
bool print_choice(int choice);
void list_menu();
bool list_choice(int choice);
void list_employees();

vector<Employee*> employees;

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
		 << "1. Add an employee" << endl
		 << "2. Remove an employee" << endl
		 << "3. Edit an existing employee" << endl
		 << "4. Load employee information" << endl
		 << "5. Save employee information" << endl
		 << "6. Print checks" << endl
		 << "7. List employees" << endl
		 << "8. Quit" << endl
		 << endl
		 << "Please enter your choice: ";
	while(!(cin >> choice)) {
		cout << "Invalid input, please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	if(choice == 8) return false;
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
			break;
		case 2:
			remove_menu();
			return true;
			break;
		case 3:
			edit_menu();
			return true;
			break;
		case 4:
			load();
			return true;
			break;
		case 5:
			save();
			return true;
			break;
		case 6:
			print_menu();
			return true;
			break;
		case 7:
			list_menu();
			return true;
			break;
		default:
			cout << "Invalid choice, please try again: ";
			return false;
			break;
	}
}

void add_menu()
{
	int choice;
	system("clear");
	cout << "What type of employee would you like to add?" << endl
		 << endl
		 << "1. Administrator" << endl
		 << "2. Salaried Employee" << endl
		 << "3. Generic Employee" << endl
		 << endl
		 << "Please enter your choice (-1 to quit): ";
	while(!((cin >> choice) && add_choice(choice))) {
	 	cout << "Invalid choice, please try again: ";
	 	cin.clear();
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

bool add_choice(int choice) 
{
	if(choice == -1) return true;
	else if(choice == 1) {
		Administrator* tom = new Administrator;
		cout << endl;
		tom->read_input();
		employees.push_back(tom);
		return true;
	}
	else if(choice == 2) {
		SalariedEmployee* dick = new SalariedEmployee;
		cout << endl;
		dick->read_input();
		employees.push_back(dick);
		return true;
	}
	else if(choice == 3) {
		Employee* harry = new Employee;
		cout << endl;
		harry->read_input();
		employees.push_back(harry);
		return true;
	}
	else {
		return false;
	}
	return false;
}

void remove_menu()
{
	int choice;
	system("clear");
	cout << "Which employee would you like to remove?\n" << endl;
	list_employees();
	cout << endl;
	cout << "Please enter your choice (-1 to quit): ";
	while(!(cin >> choice) || !remove_choice(choice)) {
	 	cout << "Invalid choice, please try again: ";
	 	cin.clear();
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

bool remove_choice(int choice)
{ 
	if(choice == -1) return true;
	if(choice > (int)employees.size() || choice < 1) return false;
	employees.erase(employees.begin() + choice -1);
	return true;
}

void edit_menu()
{
	int choice;
	system("clear");
	cout << "Which Employee would you like to edit?" << endl << endl;
	list_employees();
	cout << endl << "Please enter your choice (-1 to quit): ";
	while(!(cin >> choice) || !edit_choice(choice)) {
	 	cout << "Invalid choice, please try again: ";
	 	cin.clear();
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

bool edit_choice(int choice)
{
	if(choice == -1) return true;
	if(choice < 1 || choice > (int)employees.size()) return false;
	cout << endl;
	employees[choice - 1]->read_input();
	return true;
}

void list_employees()
{
	for(int i = 0; i < (int)employees.size(); ++i) {
		cout << i+1 << ". " << employees[i]->get_name() << endl;
	}
}

void list_menu()
{
	system("clear");
	int choice;
	cout << "Which employee would you like to view?" << endl << endl;
	list_employees();
	cout << endl;
	cout << "Please enter your choice (-1 to quit): ";
	while(!(cin >> choice) || !list_choice(choice)) {
	 	cout << "Invalid choice, please try again: ";
	 	cin.clear();
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

bool list_choice(int choice)
{
	if(choice == -1) return true;
	if(choice < 1 || choice > (int)employees.size()) return false;
	system("clear");
	employees[choice - 1]->print();
	cout << "Press Enter to continue: ";
	cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return true;
}

void print_menu()
{
	system("clear");
	int choice;
	cout << "Which employee's check would you like to print?" << endl << endl;
	list_employees();
	cout << endl
	     << "Please enter your choice (-1 to quit): ";
	while(!(cin >> choice) || !print_choice(choice)) {
	 	cout << "Invalid choice, please try again: ";
	 	cin.clear();
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

bool print_choice(int choice)
{
	if(choice == -1) return true;
	if(choice < 1 || choice > (int)employees.size()) return false;
	system("clear");
	employees[choice - 1]->print_check();
	cout << endl
		 << "Press Enter to continue: ";
	cin.get();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return true;
}

void save()
{
	for(unsigned int i = 0; i < employees.size(); ++i) {
		stringstream filename(stringstream::in|stringstream::out);
		filename << i << ".dat";
		employees[i]->serialize(filename.str().c_str());
	}
}

void load()
{
	int x = 0;
	string filename = "0.dat";
	string type;
	ifstream in(filename.c_str());
	
	while(in.good()) {
		in >> type;
		if(type == "Administrator") {
			Administrator* tom = new Administrator;
			employees.push_back(tom);
		}
		else if(type == "Salaried") {
			SalariedEmployee* dick = new SalariedEmployee;
			employees.push_back(dick);
		}
		else if(type == "Employee") {
			Employee* harry = new Employee;
			employees.push_back(harry);
		}
		else {
			cout << "Warning: skipping invalid data file " << x << ".dat" << endl;
			continue;
		}
		in.close();
		employees.back()->unserialize(filename.c_str());
		++x;
		stringstream fname;
		fname << x << ".dat";
		filename = fname.str();
		in.open(filename.c_str());
	}
}
