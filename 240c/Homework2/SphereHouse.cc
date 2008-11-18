#include "SphereHouse.h"
using namespace std;

string SphereHouse::serialize() {
    stringstream output;
    output << TwoOptionHouse::serialize() << ' ';
    output << radius << ' ' << theta << ' ' << phi;
    return output.str();
}

int SphereHouse::unserialize(string data) {
    stringstream input(data);
    input.seekg(TwoOptionHouse::unserialize(data));
    input >> radius >> theta >> phi;
    return input.tellg();
}

void SphereHouse::read(istream& in, ostream& out) {
    string input;
    TwoOptionHouse::read(in, out);
    out << "Please enter desired radius: ";
    getline(in, input); radius = atof(input.c_str());
    out << "Please enter desired horizontal angle: ";
    getline(in, input); theta = atof(input.c_str());
    out << "Please enter desired vertical angle: ";
    getline(in, input); phi = atof(input.c_str());
}

void SphereHouse::print(ostream& out) {
    TwoOptionHouse::print(out);
    out << "Radius: " << radius << endl
        << "Theta: " << theta << endl
        << "Phi: " << phi << endl;
}
