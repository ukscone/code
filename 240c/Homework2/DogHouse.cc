#include "DogHouse.h"
using namespace std;

string DogHouse::serialize() {
    stringstream output;
    output << RectangleHouse::serialize() << ' '
           << roof_type;
    return output.str();
}

int DogHouse::unserialize(string data) {
    stringstream input(data);
    input.seekg(RectangleHouse::unserialize(data));
    input >> roof_type;
    return input.tellg();
}

void DogHouse::read(istream& in, ostream& out) {
    RectangleHouse::read(in, out);
    out << "Please enter desired roof type: ";
    in >> roof_type;
}

void DogHouse::print(ostream& out) {
    RectangleHouse::print(out);
    out << "Roof style: " << roof_type << endl;
}
