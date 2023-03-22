#ifndef WEKTOR_HH
#define WEKTOR_HH

#include "LZespolona.hh"
#include "rozmiar.h"
#include <iostream>
#include <cmath>

using namespace std;

template <typename STyp, int SWymiar>
class SWektor
{
    STyp tablica[SWymiar];
    static int lacznaIlosc;
    static int aktualnaIlosc;
    public:
    SWektor() {++lacznaIlosc; ++aktualnaIlosc; for(STyp &x: tablica) x = 0;};
    SWektor(double x, double y, double z){++lacznaIlosc; ++aktualnaIlosc; tablica[0] = x; tablica[1] = y, tablica[2] = z;};
    SWektor(double x, double y){++lacznaIlosc; ++aktualnaIlosc; tablica[0] = x; tablica[1] = y;};
    SWektor(const SWektor<STyp,SWymiar>& W);
    ~SWektor(){--aktualnaIlosc;};

    STyp &operator [] (unsigned int idx) {return tablica[idx];};
    STyp operator [] (unsigned int idx) const {return tablica[idx];};
    
    SWektor<STyp, SWymiar> operator + (const SWektor<STyp, SWymiar> &Wk) const;
    SWektor<STyp, SWymiar> operator - (const SWektor<STyp, SWymiar> &Wk) const;
    STyp operator * (const SWektor<STyp, SWymiar> &Wk) const;
    SWektor<STyp, SWymiar> operator * (double &liczba) const;
    SWektor<STyp, SWymiar> operator * (LZespolona &liczba) const;
    SWektor<STyp, SWymiar> operator / (double &liczba) const;
    SWektor<STyp, SWymiar> operator / (LZespolona &liczba) const;
    bool operator == (const SWektor<STyp, SWymiar> &Wk) const;
    double operator &(const SWektor<STyp, SWymiar> &Wk) const;

    static int WyswietlLaczna(){return lacznaIlosc;}
    static int WyswietlAktualna(){return aktualnaIlosc;}
    double Odleglosc(SWektor<STyp, SWymiar> &x) const;
    //STyp DlugoscWektora() const;
};

template <typename STyp, int SWymiar>
int SWektor<STyp,SWymiar>::aktualnaIlosc = 0;

template <typename STyp, int SWymiar>
int SWektor<STyp,SWymiar>::lacznaIlosc = 0;

template <typename STyp, int SWymiar>
SWektor<STyp,SWymiar>::SWektor(const SWektor<STyp,SWymiar>& W)
{
    ++aktualnaIlosc;
    ++lacznaIlosc;
    for(unsigned int i = 0; i < SWymiar; ++i)
        tablica[i] = W[i];
}

template <typename STyp, int SWymiar>
SWektor<STyp, SWymiar> SWektor<STyp, SWymiar>::operator + (const SWektor<STyp, SWymiar> &Wk) const
{
    SWektor<STyp, SWymiar> Wynik;

    for(unsigned int i = 0; i < SWymiar; ++i)
    {
        Wynik[i] = tablica[i] + Wk[i];
    }

    return Wynik;
}

template <typename STyp, int SWymiar>
SWektor<STyp, SWymiar> SWektor<STyp, SWymiar>::operator - (const SWektor<STyp, SWymiar> &Wk) const
{
    SWektor<STyp, SWymiar> Wynik;

    for(unsigned int i = 0; i < SWymiar; ++i)
    {
        Wynik[i] = tablica[i] - Wk[i];
    }

    return Wynik;
}

template <typename STyp, int SWymiar>
STyp SWektor<STyp, SWymiar>::operator * (const SWektor<STyp, SWymiar> &Wk) const
{
    STyp wynik;
    wynik = 0;
    for(unsigned int i = 0; i < SWymiar; ++i)
    {
        wynik = ((Wk[i]*tablica[i])+wynik);
    }

    return wynik;
}

template <typename STyp, int SWymiar>
SWektor<STyp, SWymiar> SWektor<STyp, SWymiar>::operator * (double &liczba) const
{
    SWektor<STyp, SWymiar> Wynik;

    for(unsigned int i = 0; i < SWymiar; ++i)
    {
        Wynik[i] = tablica[i] * liczba;
    }

    return Wynik;
}

template <typename STyp, int SWymiar>
SWektor<STyp, SWymiar> SWektor<STyp, SWymiar>::operator * (LZespolona &liczba) const
{
    SWektor<STyp, SWymiar> Wynik;

    for(unsigned int i = 0; i < SWymiar; ++i)
    {
        Wynik[i] = tablica[i] * liczba;
    }

    return Wynik;
}

template <typename STyp, int SWymiar>
SWektor<STyp, SWymiar> SWektor<STyp, SWymiar>::operator / (double &liczba) const
{
    SWektor<STyp, SWymiar> Wynik;

    for(unsigned int i = 0; i < SWymiar; ++i)
    {
        Wynik[i] = tablica[i] / liczba;
    }

    return Wynik;
}

template <typename STyp, int SWymiar>
SWektor<STyp, SWymiar> SWektor<STyp, SWymiar>::operator / (LZespolona &liczba) const
{
    SWektor<STyp, SWymiar> Wynik;

    for(unsigned int i = 0; i < SWymiar; ++i)
    {
        Wynik[i] = tablica[i] / liczba;
    }

    return Wynik;
}

template <typename STyp, int SWymiar>
bool SWektor<STyp, SWymiar>::operator == (const SWektor<STyp, SWymiar> &Wk) const
{
    int prawda = 1;
    for(int i = 0; i < SWymiar; ++i)
    {
        if(tablica[i] != Wk[i])
            prawda = 0;
    }
    return prawda;
}

template <typename STyp, int SWymiar>
double SWektor<STyp, SWymiar>::operator & (const SWektor<STyp, SWymiar> &Wk)const
{
    return ((tablica[0]*Wk[1])-(tablica[1]*Wk[0]));
}

template <typename STyp, int SWymiar>
double SWektor<STyp, SWymiar>::Odleglosc(SWektor<STyp, SWymiar> &x) const
{
    double d = 0;
    for(int i = 0; i < SWymiar; ++i)
    {
        d += pow((tablica[i]-x[i]),2);
    }
    d = sqrt(d);
    return d;
}

template <typename STyp, int SWymiar>
std::ostream& operator << (std::ostream &sout, const SWektor<STyp, SWymiar> &Wk)
{
    for(unsigned int i = 0; i < SWymiar; ++i)
    {
        sout << Wk[i] << " ";
    }
    return sout;
}
template <typename STyp, int SWymiar>
std::istream& operator >> (std::istream &sin, SWektor<STyp, SWymiar> &Wk)
{
    for(int i = 0; i < SWymiar; ++i)
    {
        sin >> Wk[i];
        if(sin.fail())
            return sin;
    }

    return sin;
}

template <typename STyp, int SWymiar>
void WyswietlRozwiazanie(SWektor<STyp, SWymiar> rozwiazania)
{
    cout << "\n" << "Rozwiazanie x = (x1, x2, x3):" << endl;
    cout << rozwiazania << endl;
}



/*
template <typename STyp, int SWymiar>
STyp SWektor<STyp, SWymiar>::DlugoscWektora() const
{
    STyp Wynik;
    Wynik = 0;
    for(int i = 0; i < ROZMIAR; ++i)
    {
        Wynik = Wynik + (tablica[i] * tablica[i]);
    }
    Wynik = sqrt(Wynik);
    return Wynik;
}
*/
#endif
