#include <iostream>
#include <fstream> // Do pracy z plikami

using namespace std;

void Subarrays(int arr[], int n, ofstream &outputFile) {
    if (n < 2) {
        outputFile << "Brak mozliwych malejacych podciagow." << endl;
        outputFile << "Liczba malejacych podciagow: 0" << endl;
        return;
    }

    int count = 0;  // Liczba podciągów malejących
    int start = 0;  // Początek bieżącego podciągu

    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            // Kontynuujemy malejący podciąg
            continue;
        }

        // Zapisujemy zakończony podciąg
        for (int j = start; j < i - 1; ++j) {
            for (int k = j + 1; k < i; ++k) {
                outputFile << "[";
                for (int l = j; l <= k; ++l) {
                    outputFile << arr[l];
                    if (l < k) outputFile << ", ";
                }
                outputFile << "] ";
                ++count;
            }
        }
        start = i;  // Resetujemy początek nowego podciągu
    }

    // Ostatni podciąg
    for (int j = start; j < n - 1; ++j) {
        for (int k = j + 1; k < n; ++k) {
            outputFile << "[";
            for (int l = j; l <= k; ++l) {
                outputFile << arr[l];
                if (l < k) outputFile << ", ";
            }
            outputFile << "] ";
            ++count;
        }
    }

    outputFile << endl << "Liczba malejacych podciagow: " << count << endl;
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    if (!inputFile || !outputFile) {
        cerr << "Blad otwarcia pliku!" << endl;
        return 1;
    }

    int numArrays;
    inputFile >> numArrays;

    for (int i = 0; i < numArrays; ++i) {
        int n;
        inputFile >> n;

        if (n <= 0) {
            outputFile << "Tablica " << i + 1 << " jest pusta." << endl;
            continue;
        }

        int *arr = new int[n];  // Dynamiczna alokacja pamięci dla tablicy

        for (int j = 0; j < n; ++j) {
            inputFile >> arr[j];
        }

        outputFile << "Podciagi malejace w tablicy [";
        for (int j = 0; j < n; ++j) {
            outputFile << arr[j];
            if (j < n - 1) {
                outputFile << ", ";
            }
        }
        outputFile << "]:" << endl;

        Subarrays(arr, n, outputFile);

        delete[] arr;  // Zwolnienie pamięci
        outputFile << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
