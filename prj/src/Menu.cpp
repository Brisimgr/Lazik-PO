#include "Menu.hh"

using namespace std;

int Menu(Scena &Scena)
{
    char c;
    
    cout << "\n";
    Scena.getLazik()->WyswietlInformacje();
    cout << "Aktualna liczba obiektow: " << SWektor<double,3>::WyswietlAktualna() << endl;
    cout << "Laczna liczba obiektow: " << SWektor<double,3>::WyswietlLaczna() << endl;
    cout << "\n" << "\n";
    cout << "j - jazda na wprost" << endl;
    cout << "o - zmien orientacje" << endl;
    cout << "w - wybor lazika" << endl;
    cout << "m - wyswietl menu" << endl;
    cout << "l - lista probek na scenie" << endl;
    cout << "m - wyswietl menu" << endl;
    cout << "p - podjecie probki" << endl;
    cout << "k - koniec dzialania programu" << endl;
    cout << "\n";

    do
    {
        //system("clear");
        Scena.getLazik()->WyswietlInformacje();
        cout << "Twoj wybor, m - menu> ";
        cin >> c;
        cout << "\n";

        switch(c)
        {
            case 'j':
            {
                cout << "Podaj odleglosc, na ktora ma sie przemiescic lazik (w jednostkach sceny)." << endl;
                cout << "Odleglosc> ";

                double odleglosc = 0, szybkosc = 0;
                cin >> odleglosc;
                cout << "Podaj szybkosz, z jaka ma poruszac sie lazik." << endl;
                cout << "Szybkosc> ";
                cin >> szybkosc;
                Scena.getLazik()->Szybkosc() = szybkosc;
                if(cin.fail())
                    return -1;
                Scena.getLazik()->Przesuniecie(odleglosc, Scena); 
                //system("clear");
            }
            break;

            case 'o':
            {
                cout << "Podaj kat obrotu w stopniach." << endl;
                cout << "Wartosc kata> ";

                double wartoscKata = 0;
                cin >> wartoscKata;
                if(cin.fail())
                    return -1;
                Scena.getLazik()->Obrot(wartoscKata, Scena);
                //system("clear");
            }
            break;

            case 'w':
            {
                cout << "1. ----------";
                Scena(1)->WyswietlInformacje();
                cout << endl;

                cout << "2. ----------";
                Scena(2)->WyswietlInformacje();
                cout << endl;

                cout << "3. ----------";
                Scena(3)->WyswietlInformacje();
                cout << endl;

                cout << "Podaj numer lazika>";
                unsigned int numerLazika = 1;
                cin >> numerLazika;
                if(cin.fail())
                    return -1;
                Scena.ZmianaAktywnegoLazika(numerLazika);
                //system("clear");
            }
            break;

            case 'm':
            {
                //system("clear");
                Scena.getLazik()->WyswietlInformacje();
                cout << "Aktualna liczba obiektow: " << SWektor<double,3>::WyswietlAktualna() << endl;
                cout << "Laczna liczba obiektow: " << SWektor<double,3>::WyswietlLaczna() << endl;
                cout << "\n" << "\n";
                cout << "j - jazda na wprost" << endl;
                cout << "o - zmien orientacje" << endl;
                cout << "w - wybor lazika" << endl;
                cout << "m - wyswietl menu" << endl;
                cout << "l - lista probek na scenie" << endl;
                cout << "m - wyswietl menu" << endl;
                cout << "k - koniec dzialania programu" << endl;
                cout << "\n";
            }
            break;

            case 'l':
            {
                cout << "\n";
                if(Scena.getObiektySceny().empty() == true)
                {
                    cout << "Brak probke na scenie." << "\n" << "\n";
                }
                else
                {
                    cout << "Lista probek na powierzchni: " << endl;
                    Scena.WyswietlProbki();
                    cout << "\n";
                }
            }
            break;

            case 'p':
            {
                if(Scena.getLazik()->TypObiektu() == 3)
                    Scena.getLazik()->PodniesienieProbki(Scena);
                else    
                    cout << "Tylko lazik SFR moze podnosci probki." << endl;
            }
            break;

            case 'k':
            {
                cout << "Koniec programu" << endl;
                return 1;
            }
            break;

            default:
            {
                cout << "Wybrano niepoprawna opcje." << endl;
                return 0;
            }
            break;
        }



    } while (c != 'k');

    return 1;
    
}
