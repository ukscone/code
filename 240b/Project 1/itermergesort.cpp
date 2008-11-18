/* Jonathan Plona
 * January 28, 2008
 * CS 240b
 * Project 1 - Iterative MergeSort */

void iter_merge(int data[], int startL, int sizeL, int startR, int sizeR);
/* IN: Takes an array, the combined size of the sub-arrays, and a starting index.
 * OUT: Merges the two sub-arrays contained within the main array.
 */
   
void iter_merge_sort(int data[], int size);
/* IN: Takes an array, and a size.
 * OUT: Sorts the array iteratively.
 */
 
void iter_merge_sort(int data[], int size)
{    
    /*Sort the array in three stages.
     *The first stage consists of determining the biggest power 
     *of two less than the array size and sorting up to there.
     *The second stage consists of padding the remainder with zeroes
     *up to the next power of two and sorting it.  
     *In the third stage, the first two stages are merged.
     */
     
    //-------------------------STAGE 1-------------------------------

    //Find the greatest power of two that is less than the array size.
    int power = 2;
    while(power < size) {
        power *= 2;
    }
    power /= 2;
    
    //Switch each pair of elements if they are unordered.
    for(int index = 0; index < power; index += 2) {
        if(data[index] > data[index + 1]) {
            int temp = data[index];
            data[index] = data[index + 1];
            data[index + 1] = temp;
        }
    }
    
    //Merge sub-arrays of length 2, then length 4, etc. up to length 'power/2'
    for(int length = 2; length <= power/2; length *= 2) {
        for(int index = 0; index < power; index += 2*length) {
           iter_merge(data, index, length, index + length, length);
        }
    }
    
    //-------------------------STAGE 2-------------------------------
    
    //Find the first power of two greater than the size of the remainder.
    int size2 = size - power;
    int power2 = 2;
    while(power2 < size2) {
        power2 *= 2;
    }
    
    //Pad the remainder with zeroes up to that power.
    int *end = new int[power2];
    for(int index = 0; index < power2; ++index) {
        if(index < size2) {
            end[index] = data[power + index];
        }
        else {
            end[index] = 0;
        }
    }
    
    //Switch each pair of elements if they are unordered
    for(int index = 0; index < power2; index += 2) {
        if(end[index] > end[index + 1]) {
            int temp = end[index];
            end[index] = end[index + 1];
            end[index + 1] = temp;
        }
    }
    
    //Merge sub-arrays of length 2, then length 4, etc. up to length 'power/2'
    for(int length = 2; length <= power2/2; length *= 2) {
        for(int index = 0; index < power2; index += 2*length) {
           iter_merge(end, index, length, index + length, length);
        }
    }
    
    //Assign the values in the remainder (which weren't sorted in place) 
    //to the original array.
    int offset = 0;
    for(int index = 0; index < size2; ++index) {
        if(end[index + offset] == 0) {
            while(end[index + offset] == 0) {
                ++offset;
            } 
        }
        
        data[power + index] = end[index + offset];
    }
    
    //Clean up.
    delete[] end;
    
    //-------------------------STAGE 3-------------------------------
    //Merge stages 1 and 2.
    iter_merge(data, 0, power, power, size - power);    
}//iter_merge_sort

void iter_merge(int data[], int startL, int sizeL, int startR, int sizeR)
{    
    //Declare sub-arrays 'left' and 'right'
    int *right = new int[sizeR];
    int *left = new int[sizeL];
    
    //Fill sub-arrays
    for(int x = startR; x < startR + sizeR; ++x) {
        right[x - startR] = data[x];
    }
    for(int x = startL; x < startL + sizeL; ++x) {
        left[x - startL] = data[x];
    }
    
    //Computer upper and lower bounds
    int lower_bound = startL;
    int upper_bound = startR + sizeR;
    
    //Create access indices to the arrays
    int l = 0, r = 0;
    
    //Loop through the section of the array we're merging
    for(int x = lower_bound; x < upper_bound; ++x) {
        //Create a variable to store the smallest element.
        int element; 
        
        /* If both sub-arrays still contain elements, 
         * check the first element of each and assign the smaller to 'element'.
         * Otherwise, take whatever remains.
         *
         * Each time an element is taken from a sub-array,
         * and increment its access index (l or r).
         */
        if(r < sizeR && right[r] < left[l]) {
            element = right[r];
            ++r;
        }
        else if(l < sizeL) {
            element = left[l];
            ++l;
        }
        else {
            element = right[r];
            ++r;
        }
        
        //Assign element to the array.
        data[x] = element; 
    }
    //Clean up.
    delete[] right;
    delete[] left;
}//iter_merge
