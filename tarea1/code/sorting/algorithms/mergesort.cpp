//https://codesignal.com/learn/courses/sorting-and-searching-algorithms-in-cpp/lessons/exploring-merge-sort-in-cpp
// Merge dos subarrays
#include <iostream>
#include <vector>
using namespace std;

// Merge de dos sub-vectores dentro de arr
void merge(vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// MergeSort con índices, modifica el vector por referencia
void mergeSort(vector<int> &arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Función auxiliar que retorna un vector ordenado (llama a mergeSort)
vector<int> mergeSort(vector<int> arr) {
    if (!arr.empty())
        mergeSort(arr, 0, arr.size() - 1);
    return arr;
}