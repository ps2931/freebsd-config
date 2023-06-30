#include <iostream>
using namespace std;

int getMissingNumber(int a[], int n)
{
    // sort the array first
    int i = 0;
    while (i < n) {
        int correctpos = a[i] - 1;
        if(a[i] < n && a[i] != a[correctpos]) {
            swap(a[i], a[correctpos]);
        } else {
            i++;
        }
    }

    // find the missing number
    for(int i = 0; i < n; i++) {
        if (i != a[i] - 1) {
            return (i+1);
        }
    }
    return n;
}

int main() {
    int arr[] = {8, 1, 2, 3, 5, 7, 9, 6 };
    int N = sizeof(arr) / sizeof(arr[0]);

    int missedNumber = getMissingNumber(arr, N);
    cout << "missing numbser is " << missedNumber << "\n";

    return 0;
}
