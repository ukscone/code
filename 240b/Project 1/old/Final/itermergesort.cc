/* Author:  Jonathan Plona
   Date:    January 17, 2008 */

void iter_merge(int data[], int startL, int sizeL, int startR, int sizeR);
/* IN: An array, the combined size of the sub-arrays, and a starting index.
 * OUT: Merges the two sub-arrays contained within the main array.
 */
   
void iter_merge_sort(int data[], int size);
/* IN: An array, and a size.
 * OUT: Sorts the array iteratively in place.
 */
 
void iter_merge_sort(int data[], int size)
{
    int power = 2;
    while(power < size) {
        power *= 2;
    }
    power /= 2;
    
    //sort sub-arrays of size 2
    for(int index = 0; index < power; index += 2) {
        if(data[index] > data[index + 1]) {
            int temp = data[index];
            data[index] = data[index + 1];
            data[index + 1] = temp;
        }
    }
    
    //merge length 2 sub-arrays, then length 4, etc. up to power/2
    for(int length = 2; length <= power/2; length *= 2) {
        for(int index = 0; index < power; index += 2*length) {
           iter_merge(data, index, length, index + length, length);
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
    for(int length = 2; length <= power2/2; length *= 2) {
        for(int index = 0; index < power2; index += 2*length) {
           iter_merge(end, index, length, index + length, length);
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
    
    //Merge
    iter_merge(data, 0, power, power, size - power);
    
}//iter_merge_sort

void iter_merge(int data[], int startL, int sizeL, int startR, int sizeR)
{    
    //Declare sub-arrays 'left' and 'right'
    int left[sizeL];
    int right[sizeR];
    
    //Fill sub-arrays
    for(int x = startL; x < startL + sizeL; ++x) {
        left[x - startL] = data[x];
    }
    for(int x = startR; x <= startR + sizeR; ++x) {
        right[x - startR] = data[x];
    }
    
    //Create access pointers to the arrays
    int *rightptr = right;
    int *leftptr = left;
    
    //Computer upper and lower bounds
    int lower_bound = startL;
    int upper_bound = startR + sizeR;
    
    //Loop through the section of the array we're merging
    for(int x = lower_bound; x < upper_bound; ++x) {
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
        if((sizeR > 0) && (sizeL > 0)) {
            if(rightptr[0] < leftptr[0]) {
                temp = rightptr[0];
                rightptr = rightptr + 1;
                --sizeR;
            }
            else {
                temp = leftptr[0];
                leftptr = leftptr + 1;
                --sizeL;
            }
        }
        else if(sizeR > 0) {
            temp = rightptr[0];
            rightptr = rightptr + 1;
            --sizeR;
        }
        else if(sizeL > 0) {
            temp = leftptr[0];
            leftptr = leftptr + 1;
            --sizeL;
        }
        else {
            //cout << "Shouldn't be here 1" << endl; //This should never happen.
            temp = 0;
        }
        
        //Assign element to the array.
        data[x] = temp; 
    }
}//iter_merge
