#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

// <-- Funkcja pozwalająca na wyświetlanie liczb ujemnych w nawiasach.

auto drukuj_element(const int& element) -> std::ostringstream
{
    auto liczba_druk = std::ostringstream{};

    if (element < 0) {
        liczba_druk << "(" << element << ")";
    } else {
        liczba_druk << element;
    }

    return liczba_druk;
}

// <-- Funkcja pozwalająca na wybranie wiersza lub kolumny macierzy (wiersza
// macierzy transponowanej) zawierającego (zawierającej) najwięcej elementów o
// wartości 0.

auto wybierz_wiersz(const std::vector<std::vector<int>> macierz,
                    const std::vector<std::vector<int>> macierz_t,
                    bool& czy_transponowana) -> int
{
    auto wybrany_wiersz = int{};
    auto wiersz_licznik = int{};

    // Poniższa pętla służy zliczeniu, ile elementów o wartości 0 znajduje się w
    // każdym z wierszy macierzy. Jeżeli ilość elementów jest większa, niż
    // zapisana w zmiennej „wiersz_licznik”, to jest ona nadpisywana. Jeżeli
    // liczba elementów o wartości zero jest równa ilości elementów w wierszu
    // (wszystkie elementy mają wartość 0), to pętla jest przerywana, a funkcja
    // zakańczana.
    for (auto i = size_t{0}; i < macierz.size(); i++) {
        auto licznik = std::count(macierz[i].begin(), macierz[i].end(), 0);
        if (licznik > wiersz_licznik) {
            wybrany_wiersz = i;
            wiersz_licznik = licznik;
            if (wiersz_licznik == static_cast<int>(macierz[i].size())) {
                return wybrany_wiersz;
            }
        }
    }

    // Poniższa pętla służy do tego samego, co pętla powyżej, ale w przypadku
    // kolumn – wierszy macierzy transponowanej. Jeżeli w którymś z wierszy w
    // tym wypadku znajduje się więcej elementów o wartości 0, niż w pętli
    // powyżej, to informacja o tym jest przekazywana poprzez zmienną
    // „czy_transponowana”.
    for (auto i = size_t{0}; i < macierz_t.size(); i++) {
        auto licznik = std::count(macierz_t[i].begin(), macierz_t[i].end(), 0);
        if (licznik > wiersz_licznik) {
            wybrany_wiersz    = i;
            wiersz_licznik    = licznik;
            czy_transponowana = true;
            if (wiersz_licznik == static_cast<int>(macierz[i].size())) {
                break;
            }
        }
    }

    return wybrany_wiersz;
}

// <-- Funkcja służąca wyliczeniu wyznacznika -->

auto oblicz_wyznacznik(const std::vector<int>& macierz_dane,
                       const int& macierz_rozmiar,
                       std::ostringstream& lista_dzialan) -> int
{
    auto wyznacznik = int{};

    // Jeżeli rozmiar macierzy jest równy 1, to jej wyznacznik odpowiada
    // wartości elementu. W innym przypadku wyznacznik wymaga obliczeń –
    // poniższy program odpowiada metodzie wyliczenia wyznacznika według
    // rozwinięcia Laplace’a.

    if (macierz_rozmiar == 1) {
        wyznacznik = macierz_dane[0];
        lista_dzialan << drukuj_element(wyznacznik).str();
    } else {
        // Utworzenie macierzy (jako dwuwymiarowej tablicy) w formie wektora
        // wektorów (wierszy macierzy) – wektora, w którym każdy wektor
        // odpowiada jednemu wierszowi macierzy. Aby wyliczyć wyznacznik
        // macierzy należy zastosować rozwinięcie Laplace’a względem i-tego
        // wiersza lub j-tej kolumny. Przy czym, rozwinięcie Laplace’a
        // zastosowane względem j-tej kolumny macierzy A odpowiada rozwinięciu
        // Laplace’a zastosowanemu względem j-tego wiersza macierzy A
        // transponowanej. Stąd też w oparciu o podane dane (elementy) tworzone
        // są dwie macierze, z których jedna jest macierzą transponowaną. W
        // oparciu o takie macierze zostanie wybrany wierszy, który zawiera
        // najwięcej elementów o wartości 0.
        auto macierz   = std::vector<std::vector<int>>{};
        auto macierz_t = std::vector<std::vector<int>>{};

        // Każda z tworzonych macierzy (każdy z wektorów) posiada tyle samo
        // wierszy (wektorów) – odpowiadających rozmiarowi macierzy.
        for (auto i = int{}; i < macierz_rozmiar; i++) {
            macierz.push_back(std::vector<int>{});
            macierz_t.push_back(std::vector<int>{});
        }

        // Następnie każda z macierzy jest uzupełniana danymi (elementami) –
        // przykładowo, w przpadku macierzy (nietransponowanej) drugi element
        // trafi do pierwszego wiersza, natomiast w przypadku macierzy
        // transponowanej – do drugiego.
        for (auto i = size_t{0}; i < macierz_dane.size(); i++) {
            auto j = static_cast<int>(i / macierz_rozmiar);
            macierz[j].push_back(macierz_dane[i]);

            auto k = static_cast<int>(i % macierz_rozmiar);
            macierz_t[k].push_back(macierz_dane[i]);
        }

        // Poniższa funkcja służy ustaleniu, który wiersz lub kolumna macierzy
        // (czyli wiersz macierzy transponowanej) zawiera najwięcej 0.
        auto czy_transponowana = bool{false};
        auto wiersz =
            int{wybierz_wiersz(macierz, macierz_t, czy_transponowana)};

        if (czy_transponowana == true) {
            macierz = macierz_t;
        }

        // Poniższa pętla służy wykonaniu obliczeń – wykonaniu obliczeń względem
        // i-tego wiersza – dla każdego elementu wybranego wiersza.
        for (auto i = int{0}; i < macierz_rozmiar; i++) {
            // Ponieważ w rozwinięcie Laplace’a stosuje się tak długo, aż uzyska
            // się macierz, której wyznacznik można obliczyć wprost (w przypadku
            // niniejszego programu – macierz o rozmiarze 1), poniżej tworzona
            // jest macierz pomniejszona o wybrany wiersz (zawierający najwięcej
            // elementów o wartości 0) oraz – w dalszej kolejności – odpowiednie
            // kolumny.
            auto macierz_mniejsza = std::vector<std::vector<int>>{macierz};
            macierz_mniejsza.erase(macierz_mniejsza.begin() + wiersz);

            auto macierz_mniejsza_dane    = std::vector<int>{};
            auto macierz_mniejsza_rozmiar = macierz_rozmiar - 1;

            // Aby uzyskać pomniejszoną macierz, z macierzy usuwane są elementy
            // składające się na daną kolumenę – odpowiadającą danemu elementowi
            // wiersza. Równolegle dane z tej macierzy (z wektora wektorów) są
            // przenoszone do wektora liczb całkowitych, zawierającego same dane
            // (elementy) składające się na pomniejszoną macierz – wektor ten
            // posłuży obliczeniu wskaźnika dla pomniejszonej macierzy.
            for (auto kazdy : macierz_mniejsza) {
                kazdy.erase(kazdy.begin() + i);

                macierz_mniejsza_dane.reserve(macierz_mniejsza_dane.size()
                                              + kazdy.size());
                macierz_mniejsza_dane.insert(
                    macierz_mniejsza_dane.end(), kazdy.begin(), kazdy.end());
            }


            // Poniżej wyliczana jest wartość, zgodnie z wzorem na rozwinięcie
            // Laplace’a – suma tych wartości stanowi wyznacznik danej macierzy.
            if (macierz[wiersz][i] != 0) {
                lista_dzialan
                    << "((-1)^(" << wiersz + 1 << "+" << i + 1 << ") * "
                    << drukuj_element(macierz[wiersz][i]).str() << " * ";
                if (macierz_mniejsza_rozmiar != 1) {
                    lista_dzialan << "(";
                }
                wyznacznik += pow((-1), (wiersz + 1) + (i + 1))
                              * macierz[wiersz][i]
                              * oblicz_wyznacznik(macierz_mniejsza_dane,
                                                  macierz_mniejsza_rozmiar,
                                                  lista_dzialan);

                if (macierz_mniejsza_rozmiar != 1) {
                    lista_dzialan << ")";
                }
                lista_dzialan << ")";
            }

            if (i != macierz_rozmiar - 1) {
                lista_dzialan << " +";
            }
        }
    }
    return wyznacznik;
}

// <-- Funkcja służąca wyświetlaniu macierzy jako dwuwymiarowej tablicy -->

auto drukuj_macierz(const std::vector<int>& macierz,
                    const int& macierz_rozmiar,
                    const int& najwiekszy_rozmiar_elementu) -> void
{
    // Pętla służąca wyświetleniu każdego z elementów; stosuję licznik „i”
    // zamiast pętli „range for”, bo ten licznik służy określeniu, czy dany
    // element jest pierwszy, czy ostatni w wierszu.
    for (auto i = size_t{0}; i < macierz.size(); i++) {
        // Jeżeli reszta z dzielenia licznika przez rozmiar macierzy jest równa
        // 0, to znaczy, że dany element jest pierwszym elementem w wierszu.
        if (static_cast<int>(i % macierz_rozmiar) == 0) {
            std::cout << "│  ";
        }

        // W przypadku, gdy dany element ma mniejszy rozmiar (np. „2”) w
        // porównaniu do innego elementu (np. „-43”), to żeby macierz
        // wyświetlała się w sposób czytelny „brakujące” znaki są uzupełniane
        // spacjami.
        std::cout << std::setw(najwiekszy_rozmiar_elementu) << std::setfill(' ')
                  << macierz[i] << "  ";

        // Jeżeli reszta z dzielenia licznika przez rozmiar macierzy jest równa
        // rozmiarowi macierzy, to znaczy, że dany element jest ostatnim
        // elementem w wierszu.
        if (static_cast<int>(i % macierz_rozmiar) == macierz_rozmiar - 1) {
            std::cout << "│\n";
        }
    }
}

// <-- Funkcja generująca losowe wartości (elementy macierzy) -->

auto wylosuj_element() -> int
{
    std::random_device rd;
    std::uniform_int_distribution<int> losowa_liczba(-101, 101);

    auto const wylosowana_liczba = losowa_liczba(rd);

    return wylosowana_liczba;
}

// <-- Funkcja główna -->

auto main(int argc, char* argv[]) -> int
{
    // W poleceniu powinny zostać podane argumenty:
    // – czy elementy macierzy mają zostać uzupełnione losowo,
    // – jaki ma być rozmiar macierzy;
    // brak podania argumentów skutkuje błędem.

    auto liczba_argumentow = int{argc};

    if (liczba_argumentow == 1) {
        std::cerr << "Błąd! Nie podano żadnych argumentów.\n";
        return 1;
    }

    // Sprawdzenie podanych argumentów, przy pomocy wektor argumentów i pętli, w
    // oparciu o założeniu, że najpierw zostaje podany argument – opcja – a
    // następnie wielkość macierzy.
    auto argumenty = std::vector<std::string>{};
    std::copy(argv + 1, argv + argc, std::back_inserter(argumenty));

    auto macierz_losowa   = bool{};
    auto drukuj_dzialania = bool{};
    auto macierz_rozmiar  = int{};

    for (auto kazdy : argumenty) {
        if (kazdy == "-r") {
            macierz_losowa = true;
        } else if (kazdy == "-v") {
            drukuj_dzialania = true;
        } else {
            auto ostatni_znak = size_t{};
            // Poniższe służy sprawdzeniu, czy podano liczbę całkowitą – a nie
            // np. tekst bądź też ułamek dziesiętny lub liczbę całkowitą i
            // tekst. W każdym przypadku skutkuje to określeniem wielkości
            // macierzy jako liczby ujemnej, co będzie skutkowało wystąpieniem
            // błędu.
            try {
                macierz_rozmiar = std::stoi(kazdy, &ostatni_znak);
                if (ostatni_znak != kazdy.size()) {
                    macierz_rozmiar = -1;
                }
            } catch (const std::exception&) {
                macierz_rozmiar = -1;
            }
            break;
        }
    }

    if (macierz_rozmiar <= 0) {
        std::cerr << "Błąd! Nie podano wielkości macierzy lub podana wielkość "
                     "nie jest prawidłowa.\n";
        return 1;
    }

    // Początkowo tworzony jest wektor zawierający dane – wartości
    // poszczególnych elementów macierzy – to następnie będzie przekształcane w
    // postać macierzy, w formie wektora wektorów (wierszy macierzy).
    auto macierz_dane                = std::vector<int>{};
    auto najwiekszy_rozmiar_elementu = size_t{};

    for (auto i = size_t{0}; i < pow(macierz_rozmiar, 2); i++) {
        auto rozmiar_elementu = size_t{};

        if (macierz_losowa == true) {
            macierz_dane.push_back(wylosuj_element());
            rozmiar_elementu = std::to_string(macierz_dane.back()).length();

        } else {
            // Poniższy fragment kodu służy „ręcznemu” uzupełnieniu elementów
            // macierzy – z bieżącą weryfikacją wpisywanych wartości (czy są to
            // liczby całkowite) oraz wyświetlaniem dotychczas wpisanych liczb.
            auto wpisana_wartosc = std::string{};

            while (true) {
                drukuj_macierz(
                    macierz_dane, macierz_rozmiar, najwiekszy_rozmiar_elementu);
                if (static_cast<int>(i % macierz_rozmiar) == 0) {
                    std::cout << " |  ";
                }
                std::getline(std::cin, wpisana_wartosc);
                try {
                    macierz_dane.push_back(
                        std::stoi(wpisana_wartosc, &rozmiar_elementu));
                } catch (const std::exception&) {
                    std::cerr << "Błąd! Podana wartość nie jest prawidłowa. "
                                 "Spróbuj ponownie:\n";
                    continue;
                }
                std::cout << "\n";
                break;
            }
        }

        // Poniższa zmienna służy określeniu, jaki rozmiar ma (liczbę znaków
        // zajmuje) określony element macierzy – tak, aby inne znaki również
        // wyświetlały się w ten sam sposób.
        if (rozmiar_elementu > najwiekszy_rozmiar_elementu) {
            najwiekszy_rozmiar_elementu = rozmiar_elementu;
        }
    }

    drukuj_macierz(macierz_dane, macierz_rozmiar, najwiekszy_rozmiar_elementu);

    auto lista_dzialan = std::ostringstream{};

    std::cout << "\nWyznacznik obliczony według rozwinięcia Laplace’a:\n"
              << oblicz_wyznacznik(macierz_dane, macierz_rozmiar, lista_dzialan)
              << "\n";

    if (drukuj_dzialania == true) {
        std::cout << "\nLista wykonanych działań:\n"
                  << lista_dzialan.str() << "\n";
    }

    return 0;
}
