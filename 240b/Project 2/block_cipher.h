/* CipherBuffer acts as an input buffer to facilitate
 * 'encryption' with a block cipher.*/

//#ifndef BLOCK_H
//#define BLOCK_H

#include <string>
#include <fstream>

using namespace std;

//CipherBuffer 
class CipherBuffer
{
    public:
    	//Constructor
        CipherBuffer(const char* filename, unsigned int blocksize);
        
        //Reads a new value to the block.
        void read_block();
        
        //Performs a block cipher encode.
        void encode();
        
        //Performs a block cipher decode.
        void decode();
        
        //Returns the characters currently held in block.
        string toString();
        
        //Returns the status of the input.
        bool good();
        
    private:
    	//Holds block of data.
        string block;
        
        unsigned int size;
        
        //Input stream
        ifstream input;
};

//#endif
