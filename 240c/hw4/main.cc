#include <iostream>
#include "reversi.h"

using namespace std;

void empty_screen();

int main() {
	Reversi rev;
	rev.init();
	rev.play();
	return 0;
}
