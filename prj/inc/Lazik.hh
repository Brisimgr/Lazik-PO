#ifndef LAZIK_HH
#define LAZIK_HH

#include <string>
#include <unistd.h>
#include "ObiektGeom.hh"

class Scena;
class LazikSFR;

class Lazik: public ObiektGeom
{
    double _KatOrientacji;
    double _Szybkosc = 0;
    double _OdlegloscDoPrzejechania;
    
    public:

    Lazik(double kat, double szybkosc, double odleglosc, const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID, SWektor<double,3> &Skala, SWektor<double,3> &Polozenie)
    :ObiektGeom(sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID, Skala, Polozenie)
    {
        _KatOrientacji = kat;
        _Szybkosc = szybkosc;
        _OdlegloscDoPrzejechania = odleglosc;
    }

    virtual int TypObiektu() const override{return 1;};

    double Kat()const{return _KatOrientacji;};
    double &Kat(){return _KatOrientacji;};

    void DodajKat(double kat){_KatOrientacji += kat;};

    double Szybkosc()const{return _Szybkosc;};
    double &Szybkosc(){return _Szybkosc;};

    double Odleglosc()const{return _OdlegloscDoPrzejechania;};
    double &Odleglosc(){return _OdlegloscDoPrzejechania;};

    virtual void Przesuniecie(double odleglosc, Scena &Scena);

    void Obrot(double kat, Scena &Scena);

    Wektor2D WektorPredkosci()const;

    void WyswietlInformacje();

    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const override;	

    void PodniesienieProbki(Scena &S);

};


#endif
