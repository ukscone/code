/* Jonathan Plona
 * January 28, 2008
 * CS 240b
 * Project 1 - Recursive MergeSort */
   
void merge_sort(int data[], int size, int start);
/* IN: Takes an array, a size, and a starting index.
 * OUT: Sorts the array.
 */
 
void merge(int data[], int size, int start);
/* IN: Takes an array, the combined size of the sub-arrays, and a starting index.
 * OUT: Merges the two sub-arrays contained within the main array.
 */
 
void merge_sort_pub(int data[], int size);
/* IN: Takes an array and a size.
 * OUT: Calls merge_sort(data, size, 0) for compatibility.
 */
 
void merge_sort_pub(int data[], int size)
{
    //Start at the beginning
    merge_sort(data, size, 0);
}
 
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
}



void merge(int data[], int size, int start)
{
    //Compute middle and upper bounds of sub-arrays.
    int upper = start + size;
    int middle = start + size/2;
    
    //Keep track of sub-array sizes
    int lenleft = size/2;
    int lenright = size - size/2;
    
    //Declare sub-arrays 'left' and 'right'
    int *left = new int[lenleft];
    int *right = new int[lenright];
    
    //Fill sub-arrays
    for(int x = start; x < middle; ++x) {
        left[x - start] = data[x];
    }
    for(int x = middle; x < upper; ++x) {
        right[x - middle] = data[x];
    }
    
    //Create access indices to the arrays
    int l = 0, r = 0;
    
    //Loop through the section of the array we're merging
    for(int x = start; x < upper; ++x) {
        //Create a variable to store the smallest element.
        int element; 
        
        /* If both sub-arrays still contain elements, 
         * check the first element of each and assign the smaller to 'element'.
         * Otherwise, take whatever remains.
         *
         * Each time an element is taken from a sub-array,
         * and increment its access index (l or r).
         */
        if(r < lenright && right[r] < left[l]) {
            element = right[r];
            ++r;
        }
        else if(l < lenleft) {
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
}//merge
