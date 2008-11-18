#include <iostream>
#include "sorts.cpp"

using namespace std;

int main()
{
    int test_data[10] = {3, 8, 11, 12375, 66, 9, 223, 99, 100, 55};
    merge_sort(test_data, 10, 0);
    for(int x = 0; x < 10; ++x)
    {
        cout << test_data[x] << endl;
    }
    return 0;
}
/*
    for(int x = 0; x < test_size - 1; ++x) {
        if(test_data[x]>test_data[x+1]) {
            cout << "Oops, output not sorted..."<< endl;
            break;
        }
    }
*/
