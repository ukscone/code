/* Jonathan Plona
 * January 28, 2008
 * CS 240b
 * Project 1 - Simple Sort */
   
void simple_sort(int data[], int size);
/* IN: Takes an array and the array size.
 * OUT: Sorts the array.
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
}
