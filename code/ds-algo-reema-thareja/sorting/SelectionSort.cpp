#include <vector>
#include <iostream>
using namespace std;

// selection sort the array
// find min element and place it at its correct poisiton
void selectionSort(vector<int>& arr) {
    for(int i=0; i < arr.size(); i++) 
    {
        int index_of_min = i;
        for(int j=i+1; j < arr.size(); j++) 
        {
            if (arr[j] < arr[index_of_min]) 
            {
                index_of_min = j;
            } 
        }
        swap(arr[i], arr[index_of_min]);
    }
}

// fill array elements with some random integers
void fillArray(vector<int>& arr) {
    // seed for random numbers
    srand((unsigned) time(NULL));

    // fill array with random numbers
    for(int i=0; i<arr.size(); i++){
        arr[i] = 1 + (rand() % 100);
    }
}

// print array
void printArray(vector<int> arr) {
    for(auto e : arr)
        cout << e << " ";

    cout << "\n";
}


int main() {
    // initialize array with 0's
    vector<int> arr (10, 0);

    // fill array with random numbers
    fillArray(arr);

    cout << "Before: "; printArray(arr);

    selectionSort(arr);

    cout << "After: "; printArray(arr);

    return 0;
}
