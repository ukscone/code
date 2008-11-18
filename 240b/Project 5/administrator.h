#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include <string>
#include <iostream>
#include <fstream>
#include "salariedemployee.h"
using namespace std;

class Administrator : public SalariedEmployee
{
    public:
        Administrator();
        void set_supervisor(string new_supervisor);
        virtual void print() const;
        virtual void print_check();
        virtual void read_input();
        virtual void serialize(const char id[]) const;
        virtual void unserialize(const char id[]);
    private:
        string title;
        string department;
        string supervisor;
    protected:
        double annual_salary;
};

#endif
