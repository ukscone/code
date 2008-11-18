#ifndef SALARIEDEMPLOYEE_H
#define SALARIEDEMPLOYEE_H

#include <string>
#include <iostream>
#include <fstream>
#include "employee.h"
using namespace std;

class SalariedEmployee : public Employee
{
    public:
        SalariedEmployee();
        SalariedEmployee(string new_name, string new_ssn, double weekly_salary);
        
        double get_salary() const;
        void set_salary(double new_salary);
        virtual void print_check();
        
        virtual void serialize(const char id[]) const;
        virtual void unserialize(const char id[]);
        
        virtual void read_input();
        virtual void print() const;
    protected:
        double salary;
};

#endif
