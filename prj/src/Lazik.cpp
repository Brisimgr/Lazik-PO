#include "Lazik.hh"
#include "Scena.hh"
#include "LazikSFR.hh"
#include "SWektor.hh"

void Lazik::Przesuniecie(double odleglosc, Scena &Scena)
{
    bool CzyKolizja = 0;
   
    SWektor<double,3> Kierunek(1,0,0);
    Kierunek = MacierzRotacji(_KatOrientacji) * Kierunek;
    Kierunek = Kierunek * odleglosc;

    double odejmij = 0;

    double klatka = 200;
    Kierunek = Kierunek/klatka;
    for(int i = 0; i < klatka; ++i)
        {
            setPolozenie(Kierunek);
            Przelicz_i_Zapisz_Wierzcholki();

            for(std::list<std::shared_ptr <ObiektGeom> >::iterator ite = Scena.getObiektySceny().begin( ); ite != Scena.getObiektySceny().end( ); ++ite)
            {
                if((*ite != Scena.getLazik()) && ((*(*ite)).CzyKolizja(Scena.getLazik()) == TK_Kolizja))
                {
                    std::cout << "\n";
                    std::cout << "Kolizja z lazikiem o nazwie: " << (*(*ite)).WezNazweObiektu() << "\n";
                    std::cout << "\n";
                    CzyKolizja = 1;
                    ++odejmij;
                    break;
                }
            }
            
            if(CzyKolizja == 1)
            {
                Scena.gLacze().Rysuj();
                goto powrot;
            }

            Scena.gLacze().Rysuj();
            sleep(1/_Szybkosc);
        }

        
    powrot:
    if(CzyKolizja == 1)
        {
            double minus = -1;
            double piecdziesiat = 50;
            Kierunek = Kierunek * klatka;
            Kierunek = Kierunek / piecdziesiat;

            Kierunek = Kierunek * minus;
            setPolozenie(Kierunek);
            Przelicz_i_Zapisz_Wierzcholki();
        }
}  

void Lazik::Obrot(double kat, Scena &Scena)
{
    DodajKat(kat);
    MacRotacji() = MacierzRotacji(_KatOrientacji);
    Przelicz_i_Zapisz_Wierzcholki();
    Scena.gLacze().Rysuj();
}

void Lazik::WyswietlInformacje()
{
    std::cout << "Aktywny Lazik" << std::endl;
    std::cout << "Nazwa: " << getNazwaObiektu() << std::endl;
    std::cout << "Polozenie (x,y,z): " << Polozenie() << std::endl;
    std::cout << "Orientacja [st]: " << Kat() << endl;
}

Wektor2D Lazik::WektorPredkosci()const
{
    Wektor3D Predkosc3D(1,0,0);
    Wektor2D Predkosc2D;
    double szybkosc = _Szybkosc;

    Predkosc3D = (MacierzRotacji(_KatOrientacji) * Predkosc3D);
    Predkosc3D = Predkosc3D * szybkosc;

    Predkosc2D[0] = Predkosc3D[0];
    Predkosc2D[1] = Predkosc3D[1];

    return Predkosc2D;
}

TypKolizji Lazik::CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const
{
    if(PokazObrys().CzySieNaklada(WskLazik->PokazObrys()) == true)
        return TK_Kolizja;

    return TK_BrakKolizji;
}

void Lazik::PodniesienieProbki(Scena &Scena)
{
    int czyPodniosl = 0;
    for(std::list<std::shared_ptr <ObiektGeom> >::iterator ite = Scena.getObiektySceny().begin( ); ite != Scena.getObiektySceny().end( ); ++ite)
    {
        if(Scena.getLazik()->TypObiektu() == 3)
        {
            if((*ite != Scena.getLazik()) && ((*(*ite)).CzyKolizja(Scena.getLazik()) == TK_PrzejazdNadProbka))
            {
                std::dynamic_pointer_cast<LazikSFR>(Scena.getLazik())->PodjecieProbki(std::dynamic_pointer_cast<ProbkaRegolitu>((*ite)), Scena);
                cout << "Probki na laziku: " << endl;
                std::dynamic_pointer_cast<LazikSFR>(Scena.getLazik())->WyswietlPosiadaneProbki();
                czyPodniosl = 1;
                goto wyjscie;
            }
        }
    }
    if(czyPodniosl == 0)
    {
        cout << "Brak probki w okolicy." << endl;
    }
    wyjscie:{}
}

