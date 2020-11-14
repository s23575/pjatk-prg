#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
    if (argc == 1) {
        cout << "Błąd! W wierszu poleceń nie podano argumentu (liczby).\n";
        return 1;
    }

    int a;

    try {
        a = stoi(argv[1]);
    } catch (invalid_argument&) {
        cout << "Błąd! Argument podany w wierszu poleceń nie jest liczbą.\n";
        return 1;
    }

    int n;

    for (n = 1; n <= a; n++) {
        cout << n << " ";
        if (n % 3 == 0) {
            cout << "Fizz";
        }
        if (n % 5 == 0) {
            cout << "Buzz";
        }
        cout << "\n";
    }

    return 0;
}
