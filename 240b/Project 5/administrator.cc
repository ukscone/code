#include "administrator.h"
using namespace std;

Administrator::Administrator() 
                : SalariedEmployee(), title("None"), department("None"), 
                    supervisor("None"), annual_salary(0) {}

void Administrator::set_supervisor(string new_supervisor)
{
    supervisor = new_supervisor;
}

void Administrator::print() const
{
	Employee::print();
    cout << "Title:         " << title << endl
         << "Department:    " << department << endl
         << "Supervisor:    " << supervisor << endl
         << endl
         << "Annual Salary: " << annual_salary << endl
         << endl;
}

void Administrator::print_check()
{
    set_net_pay(salary);
    cout << "_________________________________" << endl
         << "Pay to the order of " << get_name() << endl
         << "The sum of " << get_net_pay() << " Dollars" << endl
         << "_________________________________" << endl
         << "Check stub NOT NEGOTIABLE " << endl
         << "Employee Number: " << get_ssn() << endl
         << "Administrative Employee. Weekly Pay: "
         << get_net_pay() << endl
         << "_________________________________" << endl;
}

void Administrator::read_input()
{
	SalariedEmployee::read_input();
	char _title[256], _department[256], _supervisor[256];
	cout << "Annual Salary: ";
	while(!(cin >> annual_salary)) {
		cout << "Annual Salary must be a number, please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	cin.ignore();
	cout << "Title: ";
	cin.getline(_title, 256, '\n');
	cout << "Department: ";
	cin.getline(_department, 256, '\n');
	cout << "Supervisor: ";
	cin.getline(_supervisor, 256, '\n');
	
	title = _title;
	department = _department;
	supervisor = _supervisor;
}

void Administrator::serialize(const char id[]) const
{
	ofstream out(id);
	out  << "Administrator\n"
		 << get_name() << "\n"
		 << get_ssn() << "\n"
		 << get_net_pay() << "\n"
		 << get_salary() << "\n"
		 << title << "\n"
		 << department << "\n"
		 << supervisor << "\n"
		 << annual_salary << "\n";
	out.close();
}

void Administrator::unserialize(const char id[])
{
	ifstream in(id);
	if (in.fail()) {
		return;
	}
	char _type[256], _name[256], _ssn[256], _title[256], _department[256], _supervisor[256];
	double _net_pay, _salary;
	string type;
	
	in.getline(_type, 256, '\n');
	type = _type;
	if(type != "Administrator") {
		cout << "\nERROR, object is of type Administrator, data is of type " << type << ", aborting this employee." << endl;
		return;
	}
	in.getline(_name, 256, '\n');
	set_name(_name);
	in.getline(_ssn, 256, '\n');
	set_ssn(_ssn);
	in >> _net_pay;
	set_net_pay(_net_pay);
	in >> _salary;
	set_salary(_salary);
	in.getline(_title, 256, '\n');
	title = _title;
	in.getline(_department, 256, '\n');
	department = _department;
	in.getline(_supervisor, 256, '\n');
	supervisor = _supervisor;
	in >> annual_salary;
	in.close();
}
