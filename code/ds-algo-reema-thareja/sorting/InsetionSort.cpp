#include <vector>
#include <iostream>
using namespace std;

void insertionSort(vector<int>& arr) 
{
    for (int i = 0; i < arr.size() - 1; i++) 
    {
        for (int j = i+1; j > 0; j--) 
        {
            if (arr[j] < arr[j-1])  std::swap(arr[j], arr[j-1]);
            else break;
        }
    }
}

// fill array elements with some random integers
void fillArray(vector<int>& arr) 
{
    // seed for random numbers
    srand((unsigned) time(NULL));

    // fill array with random numbers
    for (int i = 0; i<arr.size(); i++)
    {
        arr[i] = 1 + (rand() % 100);
    }
}

// print array
void printArray(vector<int> arr) 
{
    for(auto e : arr)
        std::cout << e << " ";

    std::cout << "\n";
}


int main() 
{
    // initialize array with 0's
    vector<int> arr (10, 0);

    // fill array with random numbers
    fillArray(arr);

    cout << "Before: "; printArray(arr);
    insertionSort(arr);
    cout << "After: "; printArray(arr);

    return 0;
}
