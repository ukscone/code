#include "RectangleHouse.h"
using namespace std;

string RectangleHouse::serialize() {
    stringstream output;
    output << TwoOptionHouse::serialize() << ' ';
    output << length << ' ' << width << ' ' << height;
    return output.str();
}

int RectangleHouse::unserialize(string data) {
    stringstream input(data);
    input.seekg(TwoOptionHouse::unserialize(data));
    input >> length >> width >> height;
    return input.tellg();
}

void RectangleHouse::read(istream& in, ostream& out) {
    string input;
    TwoOptionHouse::read(in, out);
    out << "Please enter desired length: ";
    getline(in, input); length = atof(input.c_str());
    out << "Please enter desired width: ";
    getline(in, input); width = atof(input.c_str());
    out << "Please enter desired height: ";
    getline(in, input); height = atof(input.c_str());
}

void RectangleHouse::print(ostream& out) {
    TwoOptionHouse::print(out);
    out << "Length of house: " << length << endl
        << "Width of house: " << width << endl
        << "Height of house: " << height << endl;
}
