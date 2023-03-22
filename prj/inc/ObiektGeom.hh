#ifndef OBIEKTGEOM_HH
#define OBIEKTGEOM_HH

#include <string>
#include <memory>
#include "Wektor3D.hh"
#include "SMacierz.hh"
#include "MacierzRotacji.hh"
#include "ObrysXY.hh"
#include "TypKolizji.hh"


#define NAZWA_KARTOTEKI_PLIKOW_DO_RYSOWANIA    "pliki_do_rysowania"

class Lazik;

class ObiektGeom {
    std::string   _NazwaPliku_BrylaWzorcowa;
    std::string   _NazwaPliku_BrylaRysowana;
    std::string   _NazwaObiektu;
    int           _KolorID;
    Wektor3D _Skala;
    Wektor3D _Polozenie;
    SMacierz<double,3> _MacierzRotacji;
    Obrys _Obrys;

  public:

    ObiektGeom(const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID, Wektor3D &Skala, Wektor3D &Polozenie);

    virtual ~ObiektGeom() = default;

    virtual int TypObiektu() const {return 0;};

    Wektor3D &setPolozenie(Wektor3D &Polozenie){return _Polozenie = _Polozenie + Polozenie;};

    Wektor3D Polozenie()const{return _Polozenie;};
    Wektor3D &Polozenie(){return _Polozenie;};

    void ZmienSkala(Wektor3D sk){_Skala = sk;};

    Obrys PokazObrys()const{return _Obrys;};

    void ZmienKolor(int ID_Koloru){_KolorID = ID_Koloru;}

    SMacierz<double,3> MacRotacji()const{return _MacierzRotacji;}
    SMacierz<double,3> &MacRotacji(){return _MacierzRotacji;}

    int WezKolorID() const { return _KolorID; }
  
    const std::string & WezNazweObiektu() const { return _NazwaObiektu; }
    std::string getNazwaObiektu() const {return _NazwaObiektu;};
  
    const std::string & WezNazwePliku_BrylaRysowana() const
                 { return _NazwaPliku_BrylaRysowana; }

    Wektor2D Polozenie2D()const;

    bool Przelicz_i_Zapisz_Wierzcholki();

		virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const;		     
};


#endif
