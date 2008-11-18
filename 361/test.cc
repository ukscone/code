#include <iostream>
using namespace std;

int main() {
	int h= 0;
	
	for(int x = 9; x > 0; ++x) {
		++h;
		x >>= 1;
	}
	
	cout << h << endl;
	return 0;
}
