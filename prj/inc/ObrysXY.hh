#ifndef OBRYSXY_HH
#define OBRYSXY_HH

#include <cmath>
#include "Wektor2D.hh"

class Obrys
{
    Wektor2D _LewyDolny;
    Wektor2D _PrawyGorny;
    public:
    
    Obrys(){};
    Obrys(Wektor2D Dolny, Wektor2D Gorny){_LewyDolny = Dolny; _PrawyGorny = Gorny;};

    Wektor2D LewyDolny(){return _LewyDolny;};
    Wektor2D &setLewyDolny(){return _LewyDolny;};

    Wektor2D PrawyGorny(){return _PrawyGorny;};
    Wektor2D &setPrawyGorny(){return _PrawyGorny;};

    void WyswietlObrys()const{std::cout << "Obrys:\n" << _PrawyGorny << _LewyDolny;}

    bool CzySieNaklada(const Obrys &InnyObrys);

    void ZmienObrys(const Wektor2D &Dolny, const Wektor2D &Gorny);

    double PromienObrysu();
};

#endif
