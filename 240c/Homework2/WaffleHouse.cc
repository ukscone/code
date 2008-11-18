#include "WaffleHouse.h"
using namespace std;

string WaffleHouse::serialize() {
    stringstream output;
    output << RectangleHouse::serialize() << ' '
           << num_employees;
    return output.str();
}

int WaffleHouse::unserialize(string data) {
    stringstream input(data);
    input.seekg(RectangleHouse::unserialize(data));
    input >> num_employees;
    return input.tellg();
}

void WaffleHouse::read(istream& in, ostream& out) {
    string input;
    RectangleHouse::read(in, out);
    out << "Please enter desired number of employees: ";
    in >> input; num_employees = atoi(input.c_str());
}

void WaffleHouse::print(ostream& out) {
    RectangleHouse::print(out);
    out << "Number of employees: " << num_employees << endl;
}
