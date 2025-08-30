#include "Licentie.h"

using namespace std;

Licentie::Licentie() : licentie_nummer(0), geldig_tot(""), type("") {}

Licentie::Licentie(int nummer, const string& geldig_tot, const string& type)
    : licentie_nummer(nummer), geldig_tot(geldig_tot), type(type) {}

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