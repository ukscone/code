#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	stringstream str;
	int x = 0;
	str << x << ".dat";
	cout << str.str();
	return 0;
}
