#include <iostream>

using namespace std;

void Subarrays(int arr[], int n){
    if (n < 2) // Sprawdzamy, czy tablica ma więcej niż 2 elementy
    {
        cout << "Brak mozliwych malejacych podciagow." << endl;
        return; // Jeśli długość tablicy jest mniejsza niż 2, nie ma podciągów
    }

    int count = 0; // Zmienna przechowująca liczbę malejących podciągów
    int start = 0; // Początek aktualnego malejącego podciągu

    for (int i = 1; i < n; ++i)
    {
        if (arr[i] < arr[i - 1])
        {
            // Jeśli bieżący element jest mniejszy od poprzedniego, kontynuujemy podciąg
            continue;
        }
        else
        {
            // Jeśli sekwencja się kończy, wypisz wszystkie podciągi wynikające z aktualnej sekwencji
            for (int j = start; j < i - 1; ++j)
            {
                for (int k = j + 1; k < i; ++k)
                {
                    // Wypisujemy podciąg od j do k
                    cout << "[";
                    for (int l = j; l <= k; ++l)
                    {
                        cout << arr[l];
                        if (l < k) cout << ", ";
                    }
                    cout << "]" << ", ";
                    ++count;
                }
            }
            start = i; // Reset początku nowej sekwencji
        }
    }

    // Przetwarzamy ostatni podciąg, jeśli zakończył się na końcu tablicy
    for (int j = start; j < n - 1; ++j)
    {
        for (int k = j + 1; k < n; ++k)
        {
            // Wypisujemy podciąg od j do k
            cout << "[";
            for (int l = j; l <= k; ++l)
            {
                cout << arr[l];
                if (l < k) cout << ", ";
            }
            cout << "]" << endl;
            ++count;
        }
    }

    cout << "Liczba malejacych podciagow: " << count << endl;
}

int main() {
    // Przykładowa tablica
    int arr1[] = {5, 4, 2, 2, 1};
    // Rozmiar tablicy jest rowny rozmiarowi w bajtach tablicy podzielony przez rozmiar jednego elementu
    int n1 = sizeof(arr1) / sizeof(arr1[0]);

    cout<<"Podciagi malejace w tablicy [";
    for(int i=0;i<n1;i++)
    {
        cout<<arr1[i];
        if(i!=n1-1)
        {
            cout<<", ";
        }
    }
    cout<<"]: "<<endl;

    // Wywołanie funkcji
    Subarrays(arr1, n1);

    cout<<endl;

    int arr2[] = {2, 5, 3};
    // Rozmiar tablicy jest rowny rozmiarowi w bajtach tablicy podzielony przez rozmiar jednego elementu
    int n2 = sizeof(arr2) / sizeof(arr2[0]);

    cout<<"Podciagi malejace w tablicy [";
    for(int i=0;i<n2;i++)
    {
        cout<<arr2[i];
        if(i!=n2-1)
        {
            cout<<", ";
        }
    }
    cout<<"]: "<<endl;

    // Wywołanie funkcji
    Subarrays(arr2, n2);

    cout<<endl;

    int arr3[] = {1, 2, 4, 6, 7};
    // Rozmiar całej tablicy w bajtach dzielimy przez rozmiar jednego elementu w bajtach
    int n3 = sizeof(arr3) / sizeof(arr3[0]);

    cout<<"Podciagi malejace w tablicy [";
    for(int i=0;i<n3;i++)
    {
        cout<<arr3[i];
        if(i!=n3-1)
        {
            cout<<", ";
        }
    }
    cout<<"]: "<<endl;

    // Wywołanie funkcji
    Subarrays(arr3, n3);

    return 0;
}
