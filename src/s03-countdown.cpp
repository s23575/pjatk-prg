#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 1) {
        cout << "Błąd! W wierszu poleceń nie podano argumentu (dodatniej "
                "liczby całkowitej).\n";
        return 1;
    }

    int a;

    try {
        a = stoi(argv[1]);
    } catch (invalid_argument&) {
        cout << "Błąd! Argument podany w wierszu poleceń nie jest dodatnią "
                "liczbą całkowitą.\n";
        return 1;
    }

    if (a < 0) {
        cout << "Błąd! Podana liczba całkowita nie jest dodatnia.\n";
    } else {
        for (int b = a; b >= 0; b--) {
            cout << b << "...\n";
        }
    }
    return 0;
}
