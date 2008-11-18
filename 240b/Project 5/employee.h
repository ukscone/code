#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Employee
{
    public:
        Employee();
        virtual ~Employee();
        Employee(string new_name, string new_ssn);

        string get_name() const;
        string get_ssn() const;
        double get_net_pay() const;

        void set_name(string new_name);
        void set_ssn(string new_ssn);
        void set_net_pay(double new_pay);
        
        virtual void print_check();
        
        virtual void serialize(const char id[]) const;
        virtual void unserialize(const char id[]);
        virtual void read_input();
        virtual void print() const;
        
    private:
        string name;
        string ssn;
        double net_pay;
};

#endif
