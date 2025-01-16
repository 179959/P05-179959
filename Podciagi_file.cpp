#include <iostream>
#include <fstream> // Do pracy z plikami

using namespace std;

void Subarrays(int arr[], int n, ofstream &outputFile) {
    if (n < 2) {
        outputFile << "Brak mozliwych malejacych podciagow." << endl;
        return; // Jeśli długość tablicy jest mniejsza niż 2, nie ma podciągów
    }

    int count = 0; // Zmienna przechowująca liczbę malejących podciągów
    int start = 0; // Początek aktualnego malejącego podciągu

    // Zliczamy podciągi
    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            continue; // Jeśli element jest mniejszy od poprzedniego, kontynuujemy podciąg
        } else {
            // Jeśli sekwencja się kończy, wypisz wszystkie podciągi wynikające z aktualnej sekwencji
            for (int j = start; j < i - 1; ++j) {
                for (int k = j + 1; k < i; ++k) {
                    // Zwiększamy licznik i wypisujemy podciąg do pliku
                    outputFile << "[";
                    for (int l = j; l <= k; ++l) {
                        outputFile << arr[l];
                        if (l < k) outputFile << ", ";
                    }
                    outputFile << "]" << ", ";
                    ++count;
                }
            }
            start = i; // Reset początku nowej sekwencji
        }
    }

    // Przetwarzamy ostatni podciąg, jeśli zakończył się na końcu tablicy
    for (int j = start; j < n - 1; ++j) {
        for (int k = j + 1; k < n; ++k) {
            // Zwiększamy licznik i wypisujemy podciąg do pliku
            outputFile << "[";
            for (int l = j; l <= k; ++l) {
                outputFile << arr[l];
                if (l < k) outputFile << ", ";
            }
            outputFile << "]" << endl;
            ++count;
        }
    }

    // Zapisz liczbę malejących podciągów do pliku
    outputFile << "Liczba malejacych podciagow: " << count << endl;
}

int main() {
    // Otwieramy plik do odczytu
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cout << "Nie mozna otworzyc pliku wejsciowego!" << endl;
        return 1; // W przypadku błędu otwarcia pliku, kończymy program
    }

    // Otwieramy plik do zapisu
    ofstream outputFile("output.txt");
    if (!outputFile) {
        cout << "Nie mozna otworzyc pliku wyjsciowego!" << endl;
        return 1; // W przypadku błędu otwarcia pliku, kończymy program
    }

    // Wczytanie liczby tablic i ich elementów z pliku
    int numArrays;
    inputFile >> numArrays;

    // Dla każdej tablicy wczytujemy dane
    for (int i = 0; i < numArrays; ++i) {
        int n;
        inputFile >> n; // Wczytujemy rozmiar tablicy
        int arr[n]; // Deklaracja tablicy

        // Wczytanie elementów tablicy
        for (int j = 0; j < n; ++j) {
            inputFile >> arr[j];
        }

        // Wypisujemy dane na temat tablicy do pliku wyjściowego
        outputFile << "Podciagi malejace w tablicy [";
        for (int j = 0; j < n; ++j) {
            outputFile << arr[j];
            if (j != n - 1) {
                outputFile << ", ";
            }
        }
        outputFile << "]: " << endl;

        // Wywołujemy funkcję dla każdej tablicy
        Subarrays(arr, n, outputFile);
        outputFile << endl;
    }

    inputFile.close();  // Zamykanie pliku wejściowego
    outputFile.close(); // Zamykanie pliku wyjściowego

    return 0;
}
