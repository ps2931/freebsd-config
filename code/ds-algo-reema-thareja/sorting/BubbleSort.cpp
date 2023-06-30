#include <vector>
#include <iostream>
using namespace std;

// bubble sort the array
void bubbleSort(vector<int>& arr)  {
    for (int i=0; i < arr.size(); i++) 
    {
        bool isSwapped = false;
        for (int j=0; j < arr.size()-i-1; j++) 
        { 
            if(arr[j] > arr[j+1]) 
            {
                swap(arr[j], arr[j + 1]);
                isSwapped = true;
            }
        }
        // no swapping means array is sorted
        // so no need to unnecessarily run the loops
        if(isSwapped == false) break;
    }
}

// fill array elements with some random integers
void fillArray(vector<int>& arr) {
    // seed for random numbers
    srand((unsigned) time(NULL));

    // fill array with random numbers
    for (int i = 0; i < arr.size(); ++i) 
        arr[i] = 1 + (rand() % 101);
}

// print array
void printArray(vector<int> arr) {
    for(auto e : arr)
        cout << e << " ";

    cout << "\n";
}


int main() {
    // initialize array with 0's
    vector<int> arr(10, 0);

    // fill array with random numbers
    fillArray(arr);

    std::cout << "Before: "; printArray(arr);

    bubbleSort(arr);

    std::cout << "After: "; printArray(arr);

    return 0;
}
