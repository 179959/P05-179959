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


// Funkcja licząca liczbę malejących podciągów
int CountDecreasingSubarrays(int arr[], int n) {
    if (n < 2) return 0; // Brak malejących podciągów

    int count = 0; // Liczba podciągów
    int length = 1; // Długość bieżącego malejącego fragmentu

    for (int i = 1; i < n; ++i) {
        if (arr[i] < arr[i - 1]) {
            ++length; // Kontynuujemy malejący fragment
        } else {
            // Dodajemy liczbę podciągów dla zakończonego fragmentu
            count += (length * (length - 1)) / 2;
            length = 1; // Resetujemy długość fragmentu
        }
    }

    // Dodajemy podciągi z ostatniego fragmentu
    count += (length * (length - 1)) / 2;

    return count;
}

// Funkcja testująca
void RunTests() {
    // Tablica testów: {tablica, rozmiar tablicy, oczekiwany wynik}
    struct TestCase {
        int arr[10]; // Maksymalny rozmiar tablicy
        int size;
        int expected;
    };

    // Przykładowe testy
    TestCase tests[] = {
        {{5, 4, 2, 2, 1}, 5, 4},      // 4 malejące podciągi: [5,4], [5,4,2], [4,2], [2,1]
        {{2, 5, 3}, 3, 1},            // 1 malejący podciąg: [5,3]
        {{1, 2, 4, 6, 7}, 5, 0},      // Brak malejących podciągów
        {{9, 7, 5, 3, 1}, 5, 10},     // 10 malejących podciągów
        {{1}, 1, 0},                  // Tablica jednoelementowa: brak podciągów
        {{1, 1, 1}, 3, 0},            // Wszystkie elementy równe: brak malejących podciągów
        {{8, 6, 6, 5, 3, 1}, 6, 7},   // Malejące podciągi z powtórzeniami
        {{10, 9}, 2, 1},              // Jeden malejący podciąg
        {{3, 2, 1, 2, 1, 0}, 6, 7},   // Kombinacja malejących i rosnących sekwencji (6 malejacych)
    };

    // Liczba testów
    int numTests = sizeof(tests) / sizeof(tests[0]);

    // Wykonanie testów
    for (int i = 0; i < numTests; ++i) {
        int result = CountDecreasingSubarrays(tests[i].arr, tests[i].size);
        cout << "Test " << (i + 1) << ": ";
        if (result == tests[i].expected) {
            cout << "OK" << endl;
        } else {
            cout << "FAILED (expected " << tests[i].expected << ", got " << result << ")" << endl;
        }
    }
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

	cout << "Uruchamianie testow:" << endl;
    RunTests(); // Wywołanie funkcji testującej

    inputFile.close();
    outputFile.close();

    return 0;
}
