#include "House.h"
using namespace std;

void House::set_color(string _color) {
    for(unsigned int pos = _color.find(' '); pos != string::npos; pos = _color.find(' ')) {
        _color.replace(pos, 1, 1, '_');
    }
    color = _color;
}

string House::serialize() {
    stringstream output;
    output << type << ' ' << color << ' ' << cost_per_area;
    return output.str();
}

int House::unserialize(string data) {
    stringstream input(data);
    input >> color >> cost_per_area;
    return input.tellg();
}

void House::read(istream& in, ostream& out) {
    string input;
    out << "\nPlease enter desired color: ";
    getline(in, input); set_color(input);
}

void House::print(ostream& out) {
    out << "Type of animal: " << type << endl
        << "Color of house: " << color << endl;
}

bool House::yntob(string input) {
    if((input[0] == 'y') || (input[0] == 'Y')) return true;
    else return false;
}
