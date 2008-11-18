#include "DeathStar.h"
using namespace std;

string DeathStar::serialize() {
    stringstream output;
    output << SphereHouse::serialize() << ' '
           << tractor_beam_strength;
    return output.str();
}

int DeathStar::unserialize(string data) {
    stringstream input(data);
    input.seekg(SphereHouse::unserialize(data));
    input >> tractor_beam_strength;
    return input.tellg();
}

void DeathStar::read(istream& in, ostream& out) {
    string input;
    SphereHouse::read(in, out);
    out << "Please enter desired tractor beam strength: ";
    in >> input; tractor_beam_strength = atof(input.c_str());
}

void DeathStar::print(ostream& out) {
    SphereHouse::print(out);
    out << "Tractor beam strength: " << tractor_beam_strength << endl;
}
