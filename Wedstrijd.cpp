#include "Wedstrijd.h"
#include <algorithm>

using namespace std;

Wedstrijd::Wedstrijd(string wedstrijd_naam, string wedstrijd_datum, bool is_nk, bool heeft_wissels)
    : naam(wedstrijd_naam), datum(wedstrijd_datum), is_nk(is_nk), met_wissels(heeft_wissels) {}

void Wedstrijd::voeg_deelnemer_toe(const Deelnemer& nieuwe_deelnemer)
{
    deelnemers.push_back(nieuwe_deelnemer);
}

int Wedstrijd::aantal_deelnemers() const
{
    return static_cast<int>(deelnemers.size());
}

const vector<Deelnemer>& Wedstrijd::get_deelnemers() const
{
    return deelnemers;
}

//getters
string Wedstrijd::get_naam() const 
{
    return naam;
}

string Wedstrijd::get_datum() const 
{
    return datum;
}

bool Wedstrijd::get_met_wissels() const 
{
    return met_wissels;
}

bool Wedstrijd::get_is_nk() const
{
    return is_nk;
}

vector<Deelnemer> Wedstrijd::deelnemer_lijst_gesorteerd() const 
{
    vector<Deelnemer> kopie = deelnemers; // kopie om het origineel niet te wijzigen
    sort(kopie.begin(), kopie.end(),
        [](const Deelnemer& eerste, const Deelnemer& tweede)
        {
            return eerste.totale_tijd() < tweede.totale_tijd();
        });
    return kopie;
}