#include "PolarBearIgloo.h"
using namespace std;

string PolarBearIgloo::serialize() {
    stringstream output;
    output << SphereHouse::serialize() << ' '
           << latitude;
    return output.str();
}

int PolarBearIgloo::unserialize(string data) {
    stringstream input(data);
    input.seekg(SphereHouse::unserialize(data));
    input >> latitude;
    return input.tellg();
}

void PolarBearIgloo::read(istream& in, ostream& out) {
    string input;
    SphereHouse::read(in, out);
    out << "Pleas enter desired latitude: ";
    in >> input; latitude = atof(input.c_str());
}

void PolarBearIgloo::print(std::ostream& out) {
    SphereHouse::print(out);
    out << "Latitude: " << latitude << endl;
}
