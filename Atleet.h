#pragma once
#include <string>
#include "Licentie.h"

using namespace std;

class Atleet {
private:
    string voornaam;
    string achternaam;
    string geboortedatum;
    char geslacht;
    Licentie licentie{0, "", ""}; // atleet start zonder ingevulde licentie

public:
    Atleet();
    Atleet(string voornaam, string achternaam, string geboortedatum, char geslacht);

    //setters
    void set_voornaam(string nieuwe_voornaam);
    void set_achternaam(string nieuwe_achternaam);
    void set_geboortedatum(string nieuwe_geboortedatum);
    void set_geslacht(char nieuw_geslacht);
    void set_licentie(const Licentie& nieuwe_licentie);

    //getters
    string get_voornaam() const;
    string get_achternaam() const;
    string get_geboortedatum() const;
    char get_geslacht() const;
    Licentie get_licentie() const;
};