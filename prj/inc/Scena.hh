#ifndef SCENA_HH
#define SCENA_HH

#include <memory>
#include <assert.h>
#include <list>
#include "ObiektGeom.hh"
#include "Lazik.hh"
#include "lacze_do_gnuplota.hh"
#include "Kolory.hh"
#include "PowierzchniaMarsa.hh"
#include "ProbkaRegolitu.hh"
#include "LazikSFR.hh"


class Scena
{
    PzG::LaczeDoGNUPlota _Lacze;
    
    std::shared_ptr<Lazik> _AktywnyLazik;
    std::list<std::shared_ptr <ObiektGeom> > _ObiektySceny;
    public:

    Scena();

    PzG::LaczeDoGNUPlota &gLacze(){return _Lacze;};
    PzG::LaczeDoGNUPlota gLacze()const{return _Lacze;};

    std::shared_ptr<Lazik> &setLazik(){return _AktywnyLazik;};
    std::shared_ptr<Lazik> getLazik()const{return _AktywnyLazik;};

    std::list<std::shared_ptr <ObiektGeom> > &getObiektySceny(){return _ObiektySceny;}

    std::shared_ptr<Lazik> operator()(unsigned int nrLazika);
    void ZmianaAktywnegoLazika(unsigned int nrLazika);
    
    void WyswietlProbki();
};



#endif
