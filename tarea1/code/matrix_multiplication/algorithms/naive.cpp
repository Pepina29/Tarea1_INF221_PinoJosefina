#include <iostream>
#include <vector>
using namespace std;

//https://www.geeksforgeeks.org/cpp/cpp-matrix-multiplication/

//Tiempo de ejecución: O(n3). 
//Memoria auxiliar: O(m1 * n2)
void naive(int n, const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    C.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}