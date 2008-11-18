#include <iostream>
#include <fstream>
#include <string>

#include "block_cipher.h"

using namespace std;

int main()
{		
	//File to decode
	const char* file = "out_text";
	
	//Declare output stream.
	ofstream outtext("decoded_text");
	
	//Declare an instance of CipherBuffer 
	CipherBuffer buff(file, 3);
	
	//Loop while input file still has characters.
	while (buff.good()) {
		buff.read_block();
		buff.decode();
		outtext << buff.toString();
    }
    
    //Clean up.
    outtext.close();
    return 0;
}
