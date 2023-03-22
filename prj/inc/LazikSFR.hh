#ifndef LAZIKSFR_HH
#define LAZIKSFR_HH
#include <memory>
#include <assert.h>
#include <list>
#include "ObiektGeom.hh"
#include "Lazik.hh"
#include "ProbkaRegolitu.hh"
#include "Scena.hh"

class LazikSFR: public Lazik
{
    std::list<std::shared_ptr <ProbkaRegolitu> > _ListaProbek;

    public:

    LazikSFR(double kat, double szybkosc, double odleglosc, const char* sNazwaPliku_BrylaWzorcowa, const char* sNazwaObiektu, int KolorID, SWektor<double,3> &Skala, SWektor<double,3> &Polozenie)
    :Lazik(kat, szybkosc, odleglosc, sNazwaPliku_BrylaWzorcowa, sNazwaObiektu, KolorID, Skala, Polozenie){}

    virtual int TypObiektu() const override{return 3;};

    std::list<std::shared_ptr <ProbkaRegolitu> > &getListaProbek(){return _ListaProbek;};

    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const override;	

    void PodjecieProbki(const std::shared_ptr<ProbkaRegolitu> &WskProbka, Scena &WskScena);

    void WyswietlPosiadaneProbki();

    void PrzesuniecieProbki(Wektor3D Kierunek);    

    virtual void Przesuniecie(double odleglosc, Scena &Scena) override;
};



#endif
