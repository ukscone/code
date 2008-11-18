/* Author:  Jonathan Plona
   Date:    January 17, 2008 */

using namespace std;

void simple_sort(int data[], int size);
/* IN: An array and the array size.
 * OUT: Sorts the array in place.
 */
 
void merge_sort(int data[], int size, int start);
/* IN: An array, a size, and a starting index.
 * OUT: Sorts the array in place.
 */

void merge(int data[], int size, int start);
/* IN: An array, the combined size of the sub-arrays, and a starting index.
 * OUT: Merges the two sub-arrays contained within the main array.
 */

void iter_merge_sort(int data[], int size);
/* IN: An array, and a size.
 * OUT: Sorts the array iteratively in place.
 */

void simple_sort(int data[], int size)
{
    //Loop through each element
    for(int a = 0; a < size - 1; ++a) {
        //For each element a, check if it is sorted with respect to each element b that comes after a.  
        //If not, switch them.
        for(int b = a + 1; b < size; ++b) {            
            if(data[a] > data[b]) {                
                int temp = data[a];
                data[a] = data[b];
                data[b] = temp;
            }
        }
    }    
}//simple_sort

void merge_sort(int data[], int size, int start)
{
    //BASE CASE
    //If sub-array is size 1, it is sorted.
    if(size == 1) return;
    
    //Sort first half.
    merge_sort(data, size/2, start);
    
    //Sort second half.
    merge_sort(data, size - size/2, start + size/2);
    
    //Merge two halves.
    merge(data, size, start);    
}//merge_sort



void merge(int data[], int size, int start)
{
    //Compute middle and upper bounds of sub-arrays. ('start' is lower bound)
    int upper = start + size - 1;
    int middle = start + size/2;
    
    //Keep track of sub-array sizes
    int lenleft = size/2;
    int lenright = size - size/2;
    
    //Declare sub-arrays 'left' and 'right'
    int left[lenleft];
    int right[lenright];
    
    //Fill sub-arrays
    for(int x = start; x < middle; ++x) {
        left[x - start] = data[x];
    }
    for(int x = middle; x <= upper; ++x) {
        right[x - middle] = data[x];
    }
    
    //Create access pointers to the arrays
    int *rightptr = right;
    int *leftptr = left;
    
    //Loop through the section of the array we're merging
    for(int x = start; x <= upper; ++x) {
        //Create a variable to store the smallest element.
        int temp; 
        
        /* If both sub-arrays still contain elements, 
         * check the first element of each and assign the smaller to 'temp'.
         * Otherwise, take whatever remains.
         *
         * Each time an element is taken from a sub-array,
         * decrement that sub-array's length variable
         * and increment its access pointer.
         */
        if((lenright > 0) && (lenleft > 0)) {
            if(rightptr[0] < leftptr[0]) {
                temp = rightptr[0];
                rightptr = rightptr + 1;
                --lenright;
            }
            else {
                temp = leftptr[0];
                leftptr = leftptr + 1;
                --lenleft;
            }
        }
        else if(lenright > 0) {
            temp = rightptr[0];
            rightptr = rightptr + 1;
            --lenright;
        }
        else if(lenleft > 0) {
            temp = leftptr[0];
            leftptr = leftptr + 1;
            --lenleft;
        }
        else {
            //cout << "Shouldn't be here 1" << endl; //This should never happen.
            temp = 0;
        }
        
        //Assign element to the array.
        data[x] = temp; 
    }
}//merge

void iter_merge_sort(int data[], int size)
{
    int power = 2;
    while(power < size) {
        power *= 2;
    }
    power /= 2;
    
    //sort sub-arrays of size 2, merge; merge 4; merge 8
    
    //sort sub-arrays of size 2
    for(int index = 0; index < power; index += 2) {
        if(data[index] > data[index + 1]) {
            int temp = data[index];
            data[index] = data[index + 1];
            data[index + 1] = temp;
        }
    }
    
    //merge length 2 sub-arrays, then length 4, etc. up to power/2
    for(int length = 4; length <= power; length *= 2) {
        for(int index = 0; index < power; index += size) {
            merge(data, length, index);
        }
    }
    
    //sort and merge remainder of 'data'
    int size2 = size - power;
    int power2 = 2;
    while(power2 < size2) {
        power2 *= 2;
    }
    
    //pad with zeroes
    int end[power2];
    for(int index = 0; index < power2; ++index) {
        if(index < size2) {
            end[index] = data[power + index];
        }
        else {
            end[index] = 0;
        }
    }
    
    //sort sub-arrays of size 2
    for(int index = 0; index < power2; index += 2) {
        if(end[index] > end[index + 1]) {
            int temp = end[index];
            end[index] = end[index + 1];
            end[index + 1] = temp;
        }
    }
    
    //merge
    for(int length = 4; length <= power2; length *= 2) {
        for(int index = 0; index < power2; index += length) {
            merge(end, length, index);
        }
    }
    
    //stick 'end' to the end of 'data' where it goes
    int offset = 0;
    for(int index = 0; index < size2; ++index) {
        if(end[index + offset] == 0) {
            while(end[index + offset] == 0) {
                ++offset;
            } 
        }
        
        data[power + index] = end[index + offset];
    }
    
}//iter_merge_sort
