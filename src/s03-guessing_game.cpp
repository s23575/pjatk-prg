#include <iostream>
#include <random>

using namespace std;

int main()
{
    random_device rd;
    uniform_int_distribution<int> a(1, 100);

    int b = a(rd);
    int c;

    cout << "Zgadnij wylosowaną liczbę całkowitą od 1 do 100 - podaj liczbę:\n";


    do {
        cin >> c;

        if (!cin) {
            break;

        } else {
            if (c > b) {
                cout << "Podana liczba jest za duża!\n";
            } else {
                if (c < b) {
                    cout << "Podana liczba jest za mała!\n";
                }
            }
        }

        cout << "Zgadnij jeszcze raz:\n";

    } while (c != b);

    if (!cin) {
        cout << "Błąd! Nie podano liczby całkowitej.\n";

    } else {
        cout << "Zgadłeś! Wylosowana liczba to: " << b << "\n";
    }

    return 0;
}
