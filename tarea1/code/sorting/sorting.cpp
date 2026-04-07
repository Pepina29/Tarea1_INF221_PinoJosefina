#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <filesystem>
#include <cstdlib>
#include <ctime>
#include <sstream> 
#include <algorithm> 

using namespace std;
using namespace std::chrono;
namespace fs = std::filesystem;

vector<int> mergeSort(vector<int> arr);
void quickSort(vector<int>& arr, int low, int high);
vector<int> sortArray(vector<int>& arr);

vector<int> leerArchivo(const string& nombreArchivo) {
    ifstream file(nombreArchivo);
    vector<int> arr;
    int value;
    if (!file.is_open()) {
        cerr << "Error al abrir: " << nombreArchivo << endl;
        exit(1);
    }
    while (file >> value) arr.push_back(value);
    file.close();
    return arr;
}

double medirTiempo(const string& algoritmo, vector<int>& data) {
    auto start = high_resolution_clock::now();

    if (algoritmo == "merge") {
        data = mergeSort(data);
    } else if (algoritmo == "quick") {
        quickSort(data, 0, data.size() - 1);
    } else if (algoritmo == "sort") {
        data = sortArray(data);
    }

    auto end = high_resolution_clock::now();
    duration<double, std::milli> dur = end - start;
    return dur.count();
}

int extraerN(const fs::path& filepath) {
    string filename = filepath.stem().string(); 
    size_t pos = filename.find("_");
    if (pos == string::npos) return -1;
    return stoi(filename.substr(0, pos));
}

double getCurrentRSS_MB() {
    std::ifstream file("/proc/self/status");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("VmRSS:") == 0) {
            std::istringstream iss(line);
            std::string key, value, unit;
            iss >> key >> value >> unit;
            return std::stod(value) / 1024.0; 
        }
    }
    return 0.0;
}

int main() {
    string inputDir = "data/array_input";
    string outputDir = "data/array_output";
    string measureDir = "data/measurements";

    fs::create_directories(outputDir);
    fs::create_directories(measureDir);

    srand(time(NULL));

    vector<string> algoritmos = { "merge", "quick", "sort"};

    for (const auto& entry : fs::directory_iterator(inputDir)) {
        int n = extraerN(entry.path());
        if (n > 1000000) continue; 

        string filename = entry.path().filename().string();
        string archivoEntrada = entry.path().string();
        vector<int> data = leerArchivo(archivoEntrada);

        string archivoTiempos = measureDir + "/" + filename ;
        ofstream tiemposOut(archivoTiempos);

        string archivoSalida = outputDir + "/" + filename;
        ofstream arrayOut(archivoSalida);

        for (const string& algoritmo : algoritmos) {
            vector<int> copia = data;  // SOLO una copia por algoritmo

            double memoriaAntes = getCurrentRSS_MB();

            double tiempo = medirTiempo(algoritmo, copia);

            double memoriaDespues = getCurrentRSS_MB();
            double memoriaUsada = memoriaDespues - memoriaAntes;

            tiemposOut << filename << " | " << algoritmo << " | "
                    << tiempo << " ms | " << memoriaUsada << " MB" << endl;

            // Guardar resultado (copia ya está ordenada)
            for (size_t i = 0; i < copia.size(); i++) {
                arrayOut << copia[i];
                if (i != copia.size() - 1) arrayOut << " ";
            }
            arrayOut << " (" << algoritmo << " sort)" << endl;
        }

        tiemposOut.close();
        arrayOut.close();
    }

    cout << "Resultados guardados en: " << outputDir << " y " << measureDir << endl;
    return 0;
}