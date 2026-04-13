#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
using Clock = chrono::high_resolution_clock;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped;

    for (int i = 0; i < n - 1; i++) {
        swapped = false;

        // Cada pasada reduce en 1 el rango (los últimos i ya están ordenados)
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (!swapped) break; // arreglo ya ordenado, salir temprano
    }
}


void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i; // asume que el mínimo está en i

        // Busca si hay algo menor en el resto del arreglo
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx]) minIdx = j;

        swap(arr[i], arr[minIdx]); // coloca el mínimo en su lugar
    }
}


void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        int key = arr[i]; // elemento a insertar
        int j = i - 1;

        // Desplaza hacia la derecha mientras sean mayores que key
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key; // inserta key en el hueco que quedó
    }
}


void shellSort(vector<int>& arr) {
    int n = arr.size();

    // gap: 4 → 2 → 1 (para n=8)
    for (int gap = n / 2; gap > 0; gap /= 2) {

        // Insertion Sort pero comparando de a "gap" posiciones
        for (int i = gap; i < n; i++) {
            int temp = arr[i]; // elemento a insertar
            int j;

            // Desplaza hacia adelante mientras haya mayores
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];

            arr[j] = temp; // inserta cuando la condición es falsa
        }
    }
}


void test(vector<int> data, void(*func)(vector<int>&), const string& name) {
    auto arr = data;              // copia para no alterar el original

    auto t1 = Clock::now();       // marca tiempo de inicio
    func(arr);                    // ejecuta el algoritmo
    auto t2 = Clock::now();       // marca tiempo de fin

    // Imprime nombre y duración en microsegundos
    cout << name << " took "
         << chrono::duration_cast<chrono::microseconds>(t2 - t1).count()
         << " μs\n";
}


int main() {
    vector<int> sizes = {10, 100, 1000};

    for (int n : sizes) {
        // Genera arreglo aleatorio de tamaño n
        vector<int> data(n);
        for (int i = 0; i < n; i++) data[i] = rand();

        cout << "--- Size: " << n << " ---\n";

        // Pasa el mismo arreglo desordenado a cada algoritmo
        test(data, bubbleSort,     "Bubble Sort   ");
        test(data, selectionSort,  "Selection Sort");
        test(data, insertionSort,  "Insertion Sort");
        test(data, shellSort,      "Shell Sort    ");

        cout << "\n";
    }

    return 0;
}