#include "Atleet.h"

Atleet::Atleet(string voornaam, string achternaam, string geboortedatum, char geslacht)
    : voornaam(voornaam), achternaam(achternaam), geboortedatum(geboortedatum), geslacht(geslacht), licentie(Licentie(0, "", "", "")) {}

Atleet::Atleet() : geslacht(' '), licentie(Licentie(0, "", "", "")) {}

//Setters
void Atleet::set_voornaam(string nieuwe_voornaam)
{
    voornaam = nieuwe_voornaam;
}

void Atleet::set_achternaam(string nieuwe_achternaam)
{
    achternaam = nieuwe_achternaam;
}

void Atleet::set_geboortedatum(string nieuwe_geboortedatum)
{
    geboortedatum = nieuwe_geboortedatum;
}

void Atleet::set_geslacht(char nieuw_geslacht)
{
    geslacht = nieuw_geslacht;
}

void Atleet::set_licentie(const Licentie& nieuwe_licentie)
{
    licentie = nieuwe_licentie;
}

//Getters
string Atleet::get_voornaam() const
{
    return voornaam;
}

string Atleet::get_achternaam() const
{
    return achternaam;
}

string Atleet::get_geboortedatum() const
{
    return geboortedatum;
}

char Atleet::get_geslacht() const
{
    return geslacht;
}

Licentie Atleet::get_licentie() const
{
    return licentie;
}

Licentie& Atleet::get_licentie_ref()
{
    return licentie;
}

