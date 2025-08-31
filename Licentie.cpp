#include "Licentie.h"

using namespace std;

Licentie::Licentie() : licentie_nummer(0), geldig_tot(""), type(""), vereniging(""), doping_controles({}) {}

Licentie::Licentie(int nummer, const string& geldig_tot, const string& type, const string& vereniging)
    : licentie_nummer(nummer), geldig_tot(geldig_tot), type(type), vereniging(vereniging), doping_controles({}) {}

int Licentie::get_nummer() const
{
    return licentie_nummer;
}

string Licentie::get_geldig_tot() const
{
    return geldig_tot;
}

string Licentie::get_type() const
{
    return type;
}

string Licentie::get_vereniging() const
{
    return vereniging;
}

const vector<DopingControle>& Licentie::get_doping_controles() const
{
    return doping_controles;
}

void Licentie::set_nummer(int nummer)
{
    licentie_nummer = nummer;
}

void Licentie::set_geldig_tot(const string& geldig_tot)
{
    this->geldig_tot = geldig_tot;
}

void Licentie::set_type(const string& nieuw_type)
{
    type = nieuw_type;
}

void Licentie::set_vereniging(const string& vereniging)
{
    this->vereniging = vereniging;
}

void Licentie::voeg_dopingcontrole_toe(const DopingControle& controle)
{
    doping_controles.push_back(controle);
}
