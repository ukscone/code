#include "employee.h"
using namespace std;

Employee::Employee() : name("None"), ssn("None"), net_pay(0) {}

Employee::Employee(string new_name, string new_ssn) : name(new_name), ssn(new_ssn), net_pay(0) {}

Employee::~Employee() {}

string Employee::get_name() const
{
    return name;
}

string Employee::get_ssn() const
{
    return ssn;
}

double Employee::get_net_pay() const
{
    return net_pay;
}

void Employee::set_name(string new_name)
{
    name = new_name;
}

void Employee::set_ssn(string new_ssn)
{
    ssn = new_ssn;
}

void Employee::set_net_pay(double new_pay)
{
    new_pay = new_pay;
}

void Employee::print_check()
{
	cout << "_____________________________________________________\n"
         << "Pay to the order of " << get_name() << endl
         << "The sum of " << get_net_pay() << " Dollars\n"
         << "_______________________________________________________\n"
         << "Check stub NOT NEGOTIABLE \n"
         << "Employee Number: " << get_ssn() << endl
         << "Generic Employee. Regular Pay: "
         << net_pay << endl
         << "_______________________________________________________\n";
}

void Employee::serialize(const char id[]) const
{
	ofstream out(id);
	out  << "Employee\n"
		 << get_name() << "\n"
		 << get_ssn() << "\n"
		 << get_net_pay() << "\n";
	out.close();
}

void Employee::unserialize(const char id[])
{
	ifstream in(id);
	if (in.fail()) {
		return;
	}
	char _type[256], _name[256], _ssn[256];
	double _net_pay;
	string type;
	
	in.getline(_type, 256, '\n');
	type = _type;
	if(type != "Employee") {
		cout << "\nERROR, object is of type Generic Employee, data is of type " << type << ", aborting this employee." << endl;
		return;
	}
	in.getline(_name, 256, '\n');
	set_name(_name);
	in.getline(_ssn, 256, '\n');
	set_ssn(_ssn);
	in >> _net_pay;
	set_net_pay(_net_pay);
}

void Employee::read_input()
{
	cin.clear();
	cin.ignore();
	char _name[256], _ssn[256];
	cout << "Please enter the following information: " << endl
		 << "Name: ";
	cin.getline(_name, 256, '\n');
	cout << "Social Security Number: ";
	cin.getline(_ssn, 256, '\n');
	
	set_name(_name);
	set_ssn(_ssn);
}

void Employee::print() const
{
	cout << "Name:          " << get_name() << endl 
         << "SSN:           " << get_ssn() << endl
         << endl;
}
