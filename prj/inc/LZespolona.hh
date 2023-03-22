#ifndef LZESPOLONA_HH
#define LZESPOLONA_HH

#include<iostream>

class  LZespolona {
    double   im;    
    double   re;
  public:

    double getIm() const {return im;}
    double &setIm(){return im;} 
    double getRe() const {return re;}
    double &setRe(){return re;}

    LZespolona(){re = 0; im = 0;}
    LZespolona(double re, double im){setRe() = re; setIm() = im;}
    
    LZespolona operator = (double liczba);
    LZespolona  operator + (LZespolona  Skl1) const;
    LZespolona  operator - (LZespolona  Skl1) const;
    LZespolona  operator * (LZespolona  Skl1) const;
    LZespolona  operator * (double liczba) const;
    LZespolona  operator / (LZespolona  Skl1) const;
    bool operator ==(LZespolona Skl1) const;
    bool operator != (LZespolona Skl1) const;
    LZespolona Sprzezenie(LZespolona Skl) const;
    double Modul(LZespolona Skl) const;
};

std::ostream & operator <<(std::ostream & s, const LZespolona  &LZesp);
std::istream & operator >>(std::istream & is, LZespolona &LZesp);

#endif
