#include "ObrysXY.hh"


bool Obrys::CzySieNaklada(const Obrys &InnyObrys)
{
    if(((_LewyDolny[0] <= InnyObrys._PrawyGorny[0]) && (InnyObrys._LewyDolny[0] <= _PrawyGorny[0])) && ((_LewyDolny[1] <= InnyObrys._PrawyGorny[1]) && (InnyObrys._LewyDolny[1] <= _PrawyGorny[1])))
        return true;
    
    return false;
}

void Obrys::ZmienObrys(const Wektor2D &Dolny, const Wektor2D &Gorny)
{
    _PrawyGorny = Gorny;
    _LewyDolny = Dolny;
}

//juz nieuzywane
double Obrys::PromienObrysu()
{
    return (sqrt(pow(_PrawyGorny[0]-_LewyDolny[0],2)+pow(_PrawyGorny[1]-_LewyDolny[1],2))) / 2;
}