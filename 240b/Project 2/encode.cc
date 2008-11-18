#include <iostream>
#include <fstream>
#include <string>

#include "block_cipher.h"

using namespace std;

int main()
{	
	//File to encode
	const char* file = "in_text";
	
	//Declare output stream.
	ofstream outtext("out_text");
	
	//Declare an instance of CipherBuffer 
	CipherBuffer buff(file, 3);
	
	//Loop while input file still has characters.
	while (buff.good()) {
		buff.read_block();
		buff.encode();
		outtext << buff.toString();
    }
    
    //Clean up.
    outtext.close();
    return 0;
}
