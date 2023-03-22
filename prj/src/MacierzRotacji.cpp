#include "MacierzRotacji.hh"


SMacierz<double,3> MacierzRotacji(double kat)
{
    kat = kat * PI / 180;
    SMacierz<double,3> temp;
    temp(0,0) = cos(kat);
    temp(0,1) = -sin(kat);
    temp(1,0) = sin(kat);
    temp(1,1) = cos(kat);
    temp(2,2) = 1;

    return temp;
}
