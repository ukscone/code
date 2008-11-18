#include <string>
#include <fstream>
#include <iostream>

#include "block_cipher.h"

using namespace std;

//Constructor
CipherBuffer::CipherBuffer(const char* filename, unsigned int blocksize)
{
	size = blocksize;
	input.open(filename);
}

//Set the block.
void CipherBuffer::read_block()
{
	char temp[size];
	input.get(temp, size + 1, '|');
	block = temp;
}

//Perform a block cipher encode.
void CipherBuffer::encode()
{	
	//Check if block is a full block
	if(block.length() == size) {
	    char temp = block[0];
		for(int x = 0; x < (int)size - 1; ++x) {
			block[x] = block[x + 1];
	    }
	    block[size - 1] = temp;
    }
}

//Perform a block cipher decode.
void CipherBuffer::decode()
{	
	//Check if block is a full block
	if(block.length() == size) {
	    char temp = block[size - 1];
		for(int x = size - 1; x > 0; --x) {
			block[x] = block[x - 1];
	    }
	    block[0] = temp;
    }
}

//Return block as a string.
string CipherBuffer::toString()
{
    return block;
}

bool CipherBuffer::good()
{
	return input.good();
}
