#pragma once
#include <string>
#include <vector>
#include "Deelnemer.h"

using namespace std;

class Wedstrijd
{
private:
    string naam;
    string datum; // voor nu simpel als string "dd-mm-jjjj"

    bool is_nk
    {
        false
    };

    bool met_wissels
    {
        false
    };

    vector<Deelnemer> deelnemers;

public:
    Wedstrijd() = default;
    Wedstrijd(string wedstrijd_naam, string wedstrijd_datum, bool is_nk, bool heeft_wissels);

    // basisacties
    void voeg_deelnemer_toe(const Deelnemer& nieuwe_deelnemer);

    // simpele output (kan later klassement worden)
    int aantal_deelnemers() const;
    const vector<Deelnemer>& get_deelnemers() const;

    vector<Deelnemer> deelnemer_lijst_gesorteerd() const;

    //getters
    string get_naam() const;
    string get_datum() const;
    bool get_met_wissels() const;
    bool get_is_nk() const;
};
