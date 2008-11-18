/* Author:  Jonathan Plona
   Date:    January 16, 2008 */
 
#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <fstream>
#include "mergesort.cc"
#include "simplesort.cc"
#include "itermergesort.cc"

using namespace std;

void fill_array(int a[], int size, int seed);
/* IN: Takes an array, a size, and a seed.
 * OUT: Fills the array with pseudorandom numbers.
 */
 
void get_input(int& size, int& step, int& randseed, int& test_code);
/* IN: Takes four integer variables.
 * OUT: Takes input from the user and assigns it to the variables.
 */

void set_switches(bool switches[], int code);
/* IN: Takes an array and a test code.
 * OUT: Translates the test code into the array of booleans.
 */

double time_diff(timeval before, timeval after);
/* IN: Takes a timeval and a timeval.
 * OUT: Returns the difference between the timevals.
 */

double sort(void (*sortfunc)(int*, int), int test_data[], int test_size, int seed);
/* IN: Takes a function pointer, an array, a test size, and a seed.
 * OUT: Returns the time taken to sort the array.
 */

//Set the number of sorts
const int num_sorts = 3;

int main()
{
    //Declare an array to hold pointers to all of the sort functions.
    //Declare an array of strings to hold the name of each sort.
    //Declare an array of booleans to keep track of whether or not we should perform each sort.
    void (*sorts[num_sorts])(int*, int) = {&simple_sort, &merge_sort_pub, &iter_merge_sort};
    char *sort_names[num_sorts] = {"SimpleSort", "MergeSort-R", "MergeSort-I"};
    bool sort_switches[num_sorts];
    
    //Declare integers to hold the maximum test size, the step size between tests, 
    //the seed for rand(), and the test code.
    int max_size, step, seed, test_code;

    //Declare a double to hold the time taken for each test.
    double time_taken;

    //Open a file stream to which we will send the data.
    ofstream output("output.csv");
    
    //Get input and set the sort switches.
    get_input(max_size, step, seed, test_code);
    set_switches(sort_switches, test_code);
    
    //Declare an array to hold the data to be sorted.
    int test_data[max_size];
    
    //Output the first line of the csv file.
    output << "Data Size";
    for(int x = 0; x < num_sorts; ++x) {
        if(sort_switches[x]) output << "," << sort_names[x];
    }
    output << endl;
    
    //Loop through test sizes, starting with the step size.
    for(int test_size = step; test_size <= max_size; test_size += step) {
        cout << "Testing " << test_size << " elements..." << endl;
        output <<  test_size;
        
        //Loop through the sorts and perform each one whose sort switch is true.
        for(int x = 0; x < num_sorts; ++x) {
            if(sort_switches[x]) {
                time_taken = sort(sorts[x], test_data, test_size, seed);
                output << "," << time_taken;
            }
        }
        
        output << endl;
    }
    
    cout << "Output stored in file 'output.csv'" << endl;
    output.close();
    
    return 0;
}

double sort(void (*sortfunc)(int*, int), int test_data[], int test_size, int seed)
{
    //Create variables to store before and after times
    timeval before, after;
    
    //Reset data
    fill_array(test_data, test_size, seed);
    
    //Sort
    gettimeofday(&before, NULL);
    (*sortfunc)(test_data, test_size);
    gettimeofday(&after, NULL);
    
    //Test data to make sure it's actually sorted
    for(int x = 0; x < test_size - 1; ++x) {
        if(test_data[x]>test_data[x+1]) {
            cout << "Oops, output not sorted..."<< endl;
            break;
        }
    }
    
    //Return time taken for sort
    return time_diff(before, after);
}

void set_switches(bool sort_switches[], int code)
{
    //Translate test code into array of booleans
    for(int x = 0; x < num_sorts; ++x) {
        if(code % 2 == 0) {
            sort_switches[x] = false;
        }
        else {
            sort_switches[x] = true;
        }
        code = code >> 1;
    }  
}

void fill_array(int a[], int size, int seed)
{
    //Ensure data remains the same between tests.
    srand(seed);
    
    //Fill the array with pseudorandom values.
    for(int x = 0; x < size; ++x) {
        a[x] = rand();
    }
}

void get_input(int& size, int& step, int& randseed, int& test_code)
{
    //Prompt the user to accept default settings.
    char def;
    cout << "Would you like to accept the default settings? (y/n): ";
    cin >> def;
    
    //If default settings are declined, prompt the user for each value.
    if(def != 'Y' && def != 'y') {
        cout << "Please enter the maximum number of test data: " << endl;
        cin >> size;
        cout << "Please enter a step size: " << endl;
        cin >> step;
        cout << "Please enter a seed: " << endl;
        cin >> randseed;
        cout << "Please enter a test code: ";
        cin >> test_code;
    }
    else { //Set to defaults
        test_code = 3;
        size = 50000;
        step = 1000;
        randseed = 12345;
    }
}

double time_diff(timeval before, timeval after)
{
    //Convert all values to seconds and return the difference
    double elapsed;
    elapsed = (after.tv_sec + after.tv_usec/1000000.0) - (before.tv_sec + before.tv_usec/1000000.0);
    return elapsed;
}
