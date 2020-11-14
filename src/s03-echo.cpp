#include <iostream>
#include <string>


using namespace std;

int main(int argc, char* argv[])
{
    if (argc > 3) {
        cout << "Błąd! Podano za dużo opcji.\n";
        return 1;
    }

    string opcje[3];

    for (int i = 0; i < argc; i++) {
        opcje[i] = argv[i];
    }

    const int a = 5;

    string podarg[a];

    cout << "Podaj " << a << " dowolnych argumentów (innych niż spacja):\n";

    int i;

    for (i = 0; i <= (a - 1); i++) {
        cin >> podarg[i];
    }

    cout << "Podane argumenty to:\n";

    if (opcje[1].compare("-r") == 0) {
        for (i = (a - 1); i >= 0; i--) {
            cout << podarg[i] << " ";
            if (opcje[2].compare("-l") == 0) {
                cout << "\n";
            }
        }
    } else {
        for (i = 0; i <= (a - 1); i++) {
            cout << podarg[i] << " ";
            if (opcje[1].compare("-l") == 0) {
                cout << "\n";
            }
        }
    }

    if (opcje[1].compare("-n") == 0 || opcje[2].compare("-n") == 0) {
        cout << "\n";
    }

    return 0;
}
