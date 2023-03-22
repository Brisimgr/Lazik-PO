#ifndef PROBKAREGOLITU_HH
#define PROBKAREGOLITU_HH

#include <string>
#include <unistd.h>
#include "ObiektGeom.hh"


class ProbkaRegolitu: public ObiektGeom
{

    public:

    ProbkaRegolitu(const char* sNazwaObiektu, unsigned int KolorID, SWektor<double,3> &Skala, SWektor<double,3> &Polozenie)
    :ObiektGeom("bryly_wzorcowe/szescian2.dat", sNazwaObiektu, KolorID, Skala, Polozenie)
        
        {
        Wektor3D sk(2,6,2);
        ZmienSkala(sk);
        }

    virtual int TypObiektu() const override{ return 2 ;} // 2 jeśli jest to Regolit

    virtual TypKolizji CzyKolizja(const std::shared_ptr<Lazik> & WskLazik) const override;
};

#endif
