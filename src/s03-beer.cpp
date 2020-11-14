#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    int a;

    if (argc > 1) {
        try {
            a = stoi(argv[1]);
        } catch (invalid_argument&) {
            cout << "Błąd! Argument podany w wierszu poleceń nie jest dodatnią "
                    "liczbą całkowitą.\n";
            return 1;
        }
    } else {
        a = 99;
    }

    if (a < 0) {
        cout << "Błąd! Podana liczba całkowita nie jest dodatnia.\n";
        return 1;
    } else {
        for (int b = a; b >= 1; b--) {
            cout << b << " bottles of beer on the wall, " << b
                 << " bottles of beer.\nTake one down, pass it around, "
                 << b - 1 << " bottles of beer on the wall...\n";
        }
    }
    cout << "No more bottles of beer on the wall, no more bottles of beer.\nGo "
            "to the store and buy some more, "
         << a << "bottles of beer on the wall...\n";

    return 0;
}
