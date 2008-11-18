#include "TwoOptionHouse.h"
using namespace std;

void TwoOptionHouse::set_name(string _name) {
    for(unsigned int pos = _name.find(' '); pos != string::npos; pos = _name.find(' ')) {
        _name.replace(pos, 1, 1, '_');
    }
    name = _name;
}

string TwoOptionHouse::serialize() {
    stringstream output;
    output << House::serialize() << ' '
           << name << ' ' << opt1 << ' ' << opt2;
    return output.str();
}

int TwoOptionHouse::unserialize(string data) {
    stringstream input(data);
    input.seekg(House::unserialize(data));
    input >> name >> opt1 >> opt2;
    return input.tellg();
}

void TwoOptionHouse::read(istream& in, ostream& out) {
    string input;
    House::read(in, out);
    out << "Please enter the " << get_type() << "'s name: ";
    getline(in, input); set_name(input);
    out << "Will " << name << " require a " << opt1_name << " ? (y/n) ";
    getline(in, input); opt1 = yntob(input);
    out << "Will " << name << " require a " << opt2_name << " ? (y/n) ";
    getline(in, input); opt2 = yntob(input);    
}

void TwoOptionHouse::print(ostream& out) {
    House::print(out);
    out << "Name: " << name << endl
        << "Has " << opt1_name << ": " << btoyn(opt1) << endl
        << "Has " << opt2_name << ": " << btoyn(opt2) << endl;
}

string TwoOptionHouse::btoyn(bool val) {
    if(val) return "Yes";
    else return "No";
}
