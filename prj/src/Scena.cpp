#include "Scena.hh"

Scena::Scena()
{
    SWektor<double,3> skala;
    skala[0] = 20; skala[1] = 20; skala[2] = 10;

    SWektor<double,3> pol1;
    pol1[0] = 0; pol1[1] = 0; pol1[2] = 0;
    SWektor<double,3> pol2;
    pol2[0] = 60; pol2[1] = 0; pol2[2] = 0;
    SWektor<double,3> pol3;
    pol3[0] = 50; pol3[1] = 30; pol3[2] = 0;
    SWektor<double,3> pol4;
    pol4[0] = 80; pol4[1] = 20; pol4[2] = 0;
    SWektor<double,3> pol5;
    pol5[0] = 20; pol5[1] = 40; pol5[2] = 0;
    SWektor<double,3> pol6;
    pol6[0] = 90; pol6[1] =-40; pol6[2] = 0;
    SWektor<double,3> pol7;
    pol7[0] = -30; pol7[1] =15; pol7[2] = 0;
    SWektor<double,3> pol8;
    pol8[0] = -80; pol8[1] =-50; pol8[2] = 0;

    std::shared_ptr<LazikSFR> Ob1 = std::make_shared<LazikSFR>(0,0,0,"bryly_wzorcowe/szescian3.dat","SFR",Kolor_JasnoNiebieski,skala,pol1);
    std::shared_ptr<Lazik> Ob2 = std::make_shared<Lazik>(0,0,0,"bryly_wzorcowe/szescian3.dat","Perseverance",Kolor_Czerwony,skala,pol2);
    std::shared_ptr<Lazik> Ob3 = std::make_shared<Lazik>(0,0,0,"bryly_wzorcowe/szescian3.dat","Curiosity",Kolor_Czerwony,skala,pol3);
    std::shared_ptr<ProbkaRegolitu> Ob4 = std::make_shared<ProbkaRegolitu>("Coulettes", Kolor_Fioletowy, skala, pol4);
    std::shared_ptr<ProbkaRegolitu> Ob5 = std::make_shared<ProbkaRegolitu>("Salette", Kolor_Fioletowy, skala, pol5);
    std::shared_ptr<ProbkaRegolitu> Ob6 = std::make_shared<ProbkaRegolitu>("Dourbes", Kolor_Fioletowy, skala, pol6);
    std::shared_ptr<ProbkaRegolitu> Ob7 = std::make_shared<ProbkaRegolitu>("Robine", Kolor_Fioletowy, skala, pol7);
    std::shared_ptr<ProbkaRegolitu> Ob8 = std::make_shared<ProbkaRegolitu>("Quartie", Kolor_Fioletowy, skala, pol8);

    _ObiektySceny.push_back(Ob1);
    _ObiektySceny.push_back(Ob2);
    _ObiektySceny.push_back(Ob3);
    _ObiektySceny.push_back(Ob4);
    _ObiektySceny.push_back(Ob5);
    _ObiektySceny.push_back(Ob6);
    _ObiektySceny.push_back(Ob7);
    _ObiektySceny.push_back(Ob8);

    _AktywnyLazik = Ob1;

    _Lacze.ZmienTrybRys(PzG::TR_3D);
    _Lacze.UstawZakresX(-ROMIAR_POWIERZCHNI_X/2, ROMIAR_POWIERZCHNI_X/2);
    _Lacze.UstawZakresY(-ROMIAR_POWIERZCHNI_Y/2, ROMIAR_POWIERZCHNI_Y/2);
    _Lacze.UstawZakresZ(-0, 90);  
    _Lacze.UstawRotacjeXZ(40,60);
  
    _Lacze.Inicjalizuj();

    PzG::InfoPlikuDoRysowania *wInfoPliku;
    for(std::list<std::shared_ptr <ObiektGeom> >::iterator ite = _ObiektySceny.begin( ); ite != _ObiektySceny.end( ); ++ite)
    {
        wInfoPliku = &_Lacze.DodajNazwePliku((*(*ite)).WezNazwePliku_BrylaRysowana());
        wInfoPliku->ZmienKolor((*(*ite)).WezKolorID());
    }

    for(std::list<std::shared_ptr <ObiektGeom> >::iterator ite = _ObiektySceny.begin( ); ite != _ObiektySceny.end( ); ++ite)
    {
        (*(*ite)).Przelicz_i_Zapisz_Wierzcholki();
    }
}

std::shared_ptr<Lazik> Scena::operator()(unsigned int nrLazika)
{
    assert((nrLazika > 0) && (nrLazika < 4));
    unsigned int i = 0;
    
    for(std::list<std::shared_ptr <ObiektGeom> >::iterator ite = _ObiektySceny.begin( ); ite != _ObiektySceny.end( ); ++ite)
    {
        ++i;
        if(i == nrLazika)
        {
            return std::dynamic_pointer_cast<Lazik>(*ite);
        }
    }
    throw std::logic_error("Brak lazika");
}

void Scena::ZmianaAktywnegoLazika(unsigned int nrLazika)
{
    _AktywnyLazik->ZmienKolor(Kolor_Czerwony);
    PzG::InfoPlikuDoRysowania *wInfoPliku;
    wInfoPliku = _Lacze.ZnajdzNazwePliku(_AktywnyLazik->WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor(Kolor_Czerwony);

    _AktywnyLazik = Scena::operator()(nrLazika);
    _AktywnyLazik->ZmienKolor(Kolor_JasnoNiebieski);
    wInfoPliku = _Lacze.ZnajdzNazwePliku(_AktywnyLazik->WezNazwePliku_BrylaRysowana());
    wInfoPliku->ZmienKolor(Kolor_JasnoNiebieski);
    _AktywnyLazik->Przelicz_i_Zapisz_Wierzcholki();
    _Lacze.Rysuj();
}

void Scena::WyswietlProbki()
{
    int i = 1;
    for(std::list<std::shared_ptr <ObiektGeom> >::iterator ite = _ObiektySceny.begin( ); ite != _ObiektySceny.end( ); ++ite)
    {
        if((*(*ite)).TypObiektu() == 2)
        {
            std::cout << i << ". " << (*(*ite)).getNazwaObiektu() << "  " << (*(*ite)).Polozenie() << endl; 
            ++i;
        }
    }
}
