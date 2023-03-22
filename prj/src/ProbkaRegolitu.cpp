#include "ProbkaRegolitu.hh"
#include "Lazik.hh"

TypKolizji ProbkaRegolitu::CzyKolizja(const std::shared_ptr<Lazik> &WskLazik) const
{
    if(PokazObrys().CzySieNaklada(WskLazik->PokazObrys()) == true)
    {
        Wektor2D V = WskLazik->WektorPredkosci();
        Wektor2D r = (WskLazik->Polozenie2D() - Polozenie2D());

        double d = (fabs(r & V))/(sqrt(V*V));
        double warunekKolizji = 0.2 * 20;

        if(d > warunekKolizji)
            return TK_Kolizja;

        return TK_PrzejazdNadProbka;
    }

    return TK_BrakKolizji;
}
