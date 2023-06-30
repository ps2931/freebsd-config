#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
 * To illustrate the idea of cycle sort, consider a list with distinct elements. 
 * Given an element x, we can find the index at which it will occur in the sorted 
 * list by simply counting the number of elements in the entire list that are smaller
 * than x. Now:
 *      1. If the element is already at the correct position, do nothing
 *      2. If it is not, we will write it to the intended postion. That position is 
 *          inhabited by a different element y, which we then have to move to its correct
 *          position. This process of displacing elements to their correct positions continues 
 *          until an element is moved to the original position of x. This completes a cycle.
 * 
 * Repeating this process for every element sorts the list, 
 * with a single writing operation if and only if an element 
 * is not already at its correct position.
 */ 


void cycleSort(vector<int> &arr)
{
    int n = arr.size();

    // traverse array elements
    for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
        // pick an item
        int item = arr[cycle_start];
 
        // assume this is correct position of the item
        int correctpos = cycle_start;

        // Find the real correct position of the item,
        // by counting all smaller elements on right 
        // side of the item.
        for (int i = cycle_start + 1; i < n; i++)
            if (arr[i] < item)
                correctpos++;
 
        // If item is already in correct position
        if (correctpos == cycle_start)
            continue;
 
        // ignore all duplicate elements
        while (item == arr[correctpos])
            correctpos += 1;
 
        // put the item to it's correct position
        if (correctpos != cycle_start) {
            swap(item, arr[correctpos]);
        }
 
        // Rotate rest of the cycle
        while (correctpos != cycle_start) {
            correctpos = cycle_start;
 
            // Find correct position where we put the element
            for (int i = cycle_start + 1; i < n; i++)
                if (arr[i] < item)
                    correctpos += 1;
 
            // ignore all duplicate  elements
            while (item == arr[correctpos])
                correctpos += 1;
 
            // put the item to it's right correct position
            if (item != arr[correctpos]) {
                swap(item, arr[correctpos]);
            }
        }
    }
}

int main() {
    vector<int> arr = {9, 1, 2, 3, 10, 11, 4, 5, 6, 7, 8};

    cycleSort(arr);

    // print sorted array
    for(auto e: arr) { cout << e << ", "; }
    cout << "\n";

    return 0;
}
