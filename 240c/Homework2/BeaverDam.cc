#include "BeaverDam.h"
using namespace std;

string BeaverDam::serialize() {
    stringstream output;
    output << RectangleHouse::serialize() << ' '
           << wood_type;
    return output.str();
}

int BeaverDam::unserialize(string data) {
    stringstream input(data);
    input.seekg(RectangleHouse::unserialize(data));
    input >> wood_type;
    return input.tellg();
}

void BeaverDam::read(istream& in, ostream& out) {
    RectangleHouse::read(in, out);
    out << "Please enter desired wood type: ";
    in >> wood_type;
}

void BeaverDam::print(ostream& out) {
    RectangleHouse::print(out);
    out << "Wood type: " << wood_type << endl;
}
