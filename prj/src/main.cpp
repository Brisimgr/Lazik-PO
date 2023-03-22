#include <iostream>
#include <fstream>
#include "SWektor.hh"
#include "SMacierz.hh"
#include "MacierzRotacji.hh"
#include "lacze_do_gnuplota.hh"
#include "PowierzchniaMarsa.hh"
#include "ObiektGeom.hh"
#include "Kolory.hh"
#include "Lazik.hh"
#include "Scena.hh"
#include "Menu.hh"
#include "ProbkaRegolitu.hh"


using namespace std;


int main()
{
  {
  Scena Scena1;
  
  if (!Inicjalizuj_PowierzchnieMarsa(Scena1.gLacze())) return 1;

  Scena1.gLacze().Rysuj();

  if(Menu(Scena1) == -1)
    cout << "Blad wczytania wartosci." << endl;

  }

  cout << "Aktualna liczba obiektow: " << SWektor<double,3>::WyswietlAktualna() << endl;
  cout << "Laczna liczba obiektow: " << SWektor<double,3>::WyswietlLaczna() << endl;

}
