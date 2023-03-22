#include <iostream>
#include <fstream>
#include <cmath>
#include <limits.h>
#include "ObiektGeom.hh"
#include "Lazik.hh"


using namespace std;

ObiektGeom::ObiektGeom( const char* sNazwaPliku_BrylaWzorcowa,const char* sNazwaObiektu,int KolorID, SWektor<double,3> &Skala, SWektor<double,3> &Polozenie):
  _NazwaPliku_BrylaWzorcowa(sNazwaPliku_BrylaWzorcowa), _KolorID(KolorID)
{
  _NazwaObiektu = sNazwaObiektu;
  _NazwaPliku_BrylaRysowana = NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA;
  _NazwaPliku_BrylaRysowana += "/";
  _NazwaPliku_BrylaRysowana += sNazwaObiektu;
  _NazwaPliku_BrylaRysowana += ".dat";
  _Skala = Skala;
  _Polozenie = Polozenie;

  for(int i = 0; i < 3; ++i){_MacierzRotacji(i,i) = 1;}
}

Wektor2D ObiektGeom::Polozenie2D()const
{
  Wektor2D Polozenie2D;

  Polozenie2D[0] = _Polozenie[0];
  Polozenie2D[1] = _Polozenie[1];

  return Polozenie2D;
}

bool ObiektGeom::Przelicz_i_Zapisz_Wierzcholki()
{
  ifstream  StrmWe(_NazwaPliku_BrylaWzorcowa);
  ofstream  StrmWy(_NazwaPliku_BrylaRysowana);

  if (!(StrmWe.is_open() && StrmWy.is_open())) {
    cerr << endl << "Nie mozna otworzyc jednego z plikow:" << endl
	 << "    " << _NazwaPliku_BrylaWzorcowa << endl
	 << "    " << _NazwaPliku_BrylaRysowana << endl
	 << endl;
    return false;
  }

  SWektor<double,3> Wsp;

  int Indeks_Wiersza = 0;

  StrmWe >> Wsp;

  Wektor2D WspMin(__DBL_MAX__,__DBL_MAX__);
  Wektor2D WspMax(-(__DBL_MAX__),-(__DBL_MAX__));

  if (StrmWe.fail())return false;

  do {

   for(int i=0;i<3;++i)
   {
     Wsp[i] = (Wsp[i]*_Skala[i]);
   }
   Wsp = (_MacierzRotacji*Wsp) + _Polozenie;

   for(int i =0; i< 3; ++i)
   {
     if (abs(Wsp[i]) < 1e-100) Wsp[i] = 0;
   }

   if(Wsp[2] == 0)
   {
     if(Wsp[0] < WspMin[0]){WspMin[0] = Wsp[0];}
     if(Wsp[1] < WspMin[1]){WspMin[1] = Wsp[1];}
     if(Wsp[0] > WspMax[0]){WspMax[0] = Wsp[0];}
     if(Wsp[1] > WspMax[1]){WspMax[1] = Wsp[1];}
   }

   StrmWy << Wsp << endl;
    ++Indeks_Wiersza;
    
    if (Indeks_Wiersza >= 4) {
      StrmWy << endl;
      Indeks_Wiersza = 0;
    }
    
    StrmWe >> Wsp;
    
  } while (!StrmWe.fail());

  _Obrys.ZmienObrys(WspMin, WspMax);

  if (!StrmWe.eof()) return false;
  
  return Indeks_Wiersza == 0 && !StrmWy.fail();
}

TypKolizji ObiektGeom::CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const
{
  if(PokazObrys().CzySieNaklada(WskLazik->PokazObrys()) == true)
    return TK_Kolizja;
  
  return TK_BrakKolizji;
}
