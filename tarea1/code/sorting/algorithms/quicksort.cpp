#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
//implementacion de : https://www.geeksforgeeks.org/dsa/quicksort-using-random-pivoting/
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = low + rand() % (high - low + 1);
        int pivotValue = arr[pivotIndex];

        swap(arr[pivotIndex], arr[high]);

        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivotValue) {
                i++;
                swap(arr[i], arr[j]);
            }
        }

        swap(arr[i + 1], arr[high]);

        quickSort(arr, low, i);
        quickSort(arr, i + 2, high);
    }
}
//srand(time(NULL));  en el main 