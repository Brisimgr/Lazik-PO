#ifndef MACIERZ_HH
#define MACIERZ_HH

#include "rozmiar.h"
#include "SWektor.hh"
#include "LZespolona.hh"
#include <iostream>
#include <cassert>


template <typename MTyp,int MWymiar>
class SMacierz {
  SWektor<MTyp, MWymiar> kolumna [MWymiar];
  public:
  MTyp &operator () (unsigned int kol, unsigned int wiersz) {return kolumna[kol][wiersz];} 
  MTyp operator () (unsigned int kol, unsigned int wiersz) const {return kolumna[kol][wiersz];} 
  SWektor<MTyp, MWymiar> &Kolumna (unsigned int wiersz) {return kolumna[wiersz];} 
  SWektor<MTyp, MWymiar> Kolumna (unsigned int wiersz) const {return kolumna[wiersz];} 
  SMacierz<MTyp, MWymiar> Transponowana() const;
  SWektor<MTyp, MWymiar> operator * (const SWektor<MTyp, MWymiar> &Wk) const;
  bool operator == (const SMacierz<MTyp,MWymiar> &Mac) const;
  bool CzyZerowaMacierz() const;
  void WyzerujWiersz(unsigned int ktory);
  void ZamianaWierszy(unsigned int i, unsigned int j);
  MTyp Wyznacznik() const;
};

template <typename MTyp,int MWymiar>
SMacierz<MTyp, MWymiar> SMacierz<MTyp, MWymiar>::Transponowana() const
{
    SMacierz<MTyp, MWymiar> transp;
    for(int i = 0; i < MWymiar; ++i)
    {
        for(int j = 0; j < MWymiar; ++j)
        {
            transp(i, j) = kolumna[j][i];
        }
    }
    return transp;
}
template <typename MTyp,int MWymiar>
SWektor<MTyp, MWymiar> SMacierz<MTyp, MWymiar>::operator * (const SWektor<MTyp, MWymiar> &Wk) const
{
    SWektor<MTyp, MWymiar> Wynik;
    SMacierz<MTyp, MWymiar> Mac = Transponowana();

    for(int i = 0; i < MWymiar; ++i)
    {
        Wynik[i] = (Mac.Kolumna(i) * Wk);
    }
    return Wynik;
}

template <typename MTyp,int MWymiar>
bool SMacierz<MTyp, MWymiar>::operator == (const SMacierz<MTyp,MWymiar> &Mac) const
{
    int prawda = 1;
    for(int i = 0; i < MWymiar; ++i)
    {
        if(!(kolumna[i] == Mac.kolumna[i]))
            prawda = 0;
    }
    return prawda;
}

template <typename MTyp,int MWymiar>
bool SMacierz<MTyp, MWymiar>::CzyZerowaMacierz() const
{
    SWektor<MTyp, MWymiar> zerowy;
    for(int i = 0; i < MWymiar; ++i)
    {
        if(kolumna[i] == zerowy)
            return true;
    }
    return false;
}

template <typename MTyp,int MWymiar>
void SMacierz<MTyp, MWymiar>::WyzerujWiersz(unsigned int ktory)
{
    assert(ktory < MWymiar);
    
    for(int i = ktory + 1; i < MWymiar; ++i)
    {
        kolumna[i] = (kolumna[i] - (kolumna[ktory] * (this->kolumna[i][ktory] / this->kolumna[ktory][ktory])));
    }
}

template <typename MTyp,int MWymiar>
void SMacierz<MTyp, MWymiar>::ZamianaWierszy(unsigned int i, unsigned int j)
{
    assert((i < MWymiar) && (j < MWymiar));
    std::swap(kolumna[i], kolumna[j]);
}

template <typename MTyp,int MWymiar>
MTyp SMacierz<MTyp, MWymiar>::Wyznacznik() const
{
    SMacierz<MTyp, MWymiar> Mac = *this;
    int znak = 1;
    MTyp zero;
    zero = 0;

    if(Mac.CzyZerowaMacierz())
        return zero;

    for(int i = 0; i < (ROZMIAR - 1); ++i)
    {
        if(kolumna[i][i] == zero)
        {
            if(kolumna[i][i+1] != zero)
                Mac.ZamianaWierszy(i, i+1);
            else    
                Mac.ZamianaWierszy(i, i+2);
            znak *= -1;
        }
        Mac.WyzerujWiersz(i);
    }
    MTyp wynik = Mac(0,0);
    for(int i = 1; i < ROZMIAR; ++i)
    {
        wynik = wynik * Mac(i, i);
    }
    wynik = wynik * znak;
    return wynik;
}

template <typename MTyp,int MWymiar>
std::istream& operator >> (std::istream &sin, SMacierz<MTyp, MWymiar> &Mac)
{
  for(int i = 0; i < MWymiar; ++i)
    {
        sin >> Mac.Kolumna(i);
        if(sin.fail())
          return sin;
    }

    return sin;
}

template <typename MTyp,int MWymiar>
std::ostream& operator << (std::ostream &sout, const SMacierz<MTyp, MWymiar> &Mac)
{
  for( int i = 0; i < MWymiar; ++i)
    sout << Mac.Kolumna(i) << "\n";
  
  return sout;
}


#endif
