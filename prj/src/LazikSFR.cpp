#include "LazikSFR.hh"

TypKolizji LazikSFR::CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const
{
    if(PokazObrys().CzySieNaklada(WskLazik->PokazObrys()) == true)
        return TK_Kolizja;

    return TK_BrakKolizji;
}

void LazikSFR::PodjecieProbki(const std::shared_ptr<ProbkaRegolitu> &WskProbka, Scena &WskScena)
{
    WskScena.getObiektySceny().remove(WskProbka);

    getListaProbek().push_back(WskProbka);
}

void LazikSFR::WyswietlPosiadaneProbki()
{
    int i = 1;
    for(std::list<std::shared_ptr <ProbkaRegolitu> >::iterator ite = _ListaProbek.begin( ); ite != _ListaProbek.end( ); ++ite)
    {
        if((*(*ite)).TypObiektu() == 2)
        {
            std::cout << i << ". " << (*(*ite)).getNazwaObiektu() << "  " << (*(*ite)).Polozenie() << endl; 
            ++i;
        }
    }
    cout << "\n";
}

void LazikSFR::PrzesuniecieProbki(Wektor3D Kierunek)
{
    for(std::list<std::shared_ptr <ProbkaRegolitu> >::iterator ite = _ListaProbek.begin( ); ite != _ListaProbek.end( ); ++ite)
    {
        if((*(*ite)).TypObiektu() == 2)
        {
            (*(*ite)).setPolozenie(Kierunek);
            (*(*ite)).Przelicz_i_Zapisz_Wierzcholki();
        }
    }
}

void LazikSFR::Przesuniecie(double odleglosc, Scena &Scena)
{
    bool CzyKolizja = 0;
   
    SWektor<double,3> Kierunek(1,0,0);
    Kierunek = MacierzRotacji(this->Kat()) * Kierunek;
    Kierunek = Kierunek * odleglosc;

    double odejmij = 0;

    double klatka = 200;
    Kierunek = Kierunek/klatka;

    int czyPrzejechal = 0;

    for(int i = 0; i < klatka; ++i)
        {
            setPolozenie(Kierunek);
            Przelicz_i_Zapisz_Wierzcholki();

            for(std::list<std::shared_ptr <ObiektGeom> >::iterator ite = Scena.getObiektySceny().begin( ); ite != Scena.getObiektySceny().end( ); ++ite)
            {
                if((*ite != Scena.getLazik()) && ((*(*ite)).CzyKolizja(Scena.getLazik()) == TK_PrzejazdNadProbka) && czyPrzejechal == 0)
                {
                    std::cout << "\n" << "Przejazd nad probka: " << (*(*ite)).WezNazweObiektu() << " Mozna ja podniesc." << "\n" << "\n";
                    czyPrzejechal = 1;
                }

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

            PrzesuniecieProbki(Kierunek);
            
            if(CzyKolizja == 1)
            {
                Scena.gLacze().Rysuj();
                goto powrot;
            }

            Scena.gLacze().Rysuj();
            sleep(1/this->Szybkosc());
        }

        
    powrot:
    if(CzyKolizja == 1)
        {
            double minus = -1;
            double piecdziesiat = 50;
            Kierunek = Kierunek * klatka;
            Kierunek = Kierunek / piecdziesiat;

            Kierunek = Kierunek * minus;
            PrzesuniecieProbki(Kierunek);
            setPolozenie(Kierunek);
            Przelicz_i_Zapisz_Wierzcholki();
        }
}  



