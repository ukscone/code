#include "salariedemployee.h"
using namespace std;

SalariedEmployee::SalariedEmployee() : Employee(), salary(0) {}

SalariedEmployee::SalariedEmployee(string new_name, string new_ssn, double weekly_salary)
                : Employee(new_name, new_ssn), salary(weekly_salary) {}

double SalariedEmployee::get_salary() const
{
    return salary;
}

void SalariedEmployee::set_salary(double new_salary)
{
    salary = new_salary;
}

void SalariedEmployee::print_check()
{
    set_net_pay(salary);
    cout << "_____________________________________________________\n"
         << "Pay to the order of " << get_name() << endl
         << "The sum of " << get_net_pay() << " Dollars\n"
         << "_______________________________________________________\n"
         << "Check stub NOT NEGOTIABLE \n"
         << "Employee Number: " << get_ssn() << endl
         << "Salaried Employee. Regular Pay: "
         << get_net_pay() << endl
         << "_______________________________________________________\n";
}

void SalariedEmployee::print() const
{
	Employee::print();
	cout << "Weekly Salary: " << salary << endl
         << endl;
}

void SalariedEmployee::serialize(const char id[]) const
{
	ofstream out(id);
	out  << "Salaried\n"
		 << get_name() << "\n"
		 << get_ssn() << "\n"
		 << get_net_pay() << "\n"
		 << get_salary() << "\n";
	out.close();
}

void SalariedEmployee::unserialize(const char id[])
{
	ifstream in(id);
	if (in.fail()) {
		return;
	}
	char _type[256], _name[256], _ssn[256];
	double _net_pay, _salary;
	string type;
	
	in.getline(_type, 256, '\n');
	type = _type;
	if(type != "Salaried") {
		cout << "\nERROR, object is of type Salaried Employee, data is of type " << type << ", aborting this employee." << endl;
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
}

void SalariedEmployee::read_input()
{
	Employee::read_input();
	
	double _salary;
	cout << "Weekly Salary: ";
	while(!(cin >> _salary)) {
		cout << "Weekly Salary must be a number, please try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	set_salary(_salary);
}
