#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <thread>

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

typedef vector<vector<int>> Matrix;

Matrix strassen(const Matrix& A, const Matrix& B) ;
void naive(int n, const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C);

Matrix leerMatriz(const string& nombreArchivo, int n) {
    ifstream file(nombreArchivo);
    Matrix M(n, vector<int>(n));
    if (!file.is_open()) {
        cerr << "Error al abrir: " << nombreArchivo << endl;
        exit(1);
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            file >> M[i][j];
    return M;
}


void guardarMatriz(const string& nombreArchivo, const Matrix& M, const string& algoritmo) {
    ofstream file(nombreArchivo, ios::app);
    for (auto& fila : M) {
        for (auto& val : fila)
            file << val << " ";
        file << "\n";
    }
    file << "(" << algoritmo << ")\n\n";
}


double getCurrentRSS() {
    ifstream file("/proc/self/status");
    string line;
    while (getline(file, line)) {
        if (line.find("VmRSS:") == 0) {
            istringstream iss(line);
            string key, value, unit;
            iss >> key >> value >> unit;
            return stod(value) / 1024.0; 
        }
    }
    return 0.0;
}

pair<double, double> medirTiempo(
        const string& algoritmo,
        const Matrix& A,
        const Matrix& B,
        Matrix& C) 
{
    double memoriaPeak = 0.0;
    bool running = true;


    thread monitor([&]() {
        while (running) {
            double actual = getCurrentRSS();
            memoriaPeak = max(memoriaPeak, actual);
            this_thread::sleep_for(chrono::milliseconds(2)); 
        }
    });

    auto start = high_resolution_clock::now();
    if (algoritmo == "naive") {
        naive(A.size(), A, B, C);
    } else if (algoritmo == "strassen") {
        C = strassen(A, B);
    }
    auto end = high_resolution_clock::now();

    running = false;
    monitor.join();

    duration<double, milli> dur = end - start;
    return {dur.count(), memoriaPeak}; 
}


int main() {
    string inputDir = "data/matrix_input";
    string outputDir = "data/matrix_output";
    string measureDir = "data/measurements";

    fs::create_directories(outputDir);
    fs::create_directories(measureDir);

    vector<string> algoritmos = {"naive", "strassen"};

    for (const auto& entry : fs::directory_iterator(inputDir)) {
        string filename = entry.path().filename().string();
        if (filename.size() < 6 || filename.substr(filename.size() - 6) != "_1.txt")
            continue;

        string base = filename.substr(0, filename.size() - 6);
        string archivoM1 = entry.path().string();
        string archivoM2 = entry.path().parent_path().string() + "/" + base + "_2.txt";

        if (!fs::exists(archivoM2)) continue;

        int n = stoi(base.substr(0, base.find("_")));
        if (n > 512) continue; 
        Matrix A = leerMatriz(archivoM1, n);
        Matrix B = leerMatriz(archivoM2, n);

        string archivoTiempos = measureDir + "/" + base + "_measurement.txt";
        ofstream tiemposOut(archivoTiempos);

        string archivoSalida = outputDir + "/" + base + "_out.txt";

        for (const string& algoritmo : algoritmos) {
            Matrix C(n, vector<int>(n, 0));
            auto [tiempo, memoria] = medirTiempo(algoritmo, A, B, C);

            tiemposOut << base << " | " << algoritmo << " | "
            << fixed << setprecision(4) << tiempo << " ms | "
            << fixed << setprecision(5) << memoria << " MB" << endl;

            guardarMatriz(archivoSalida, C, algoritmo);
        }
    }

    return 0;
}