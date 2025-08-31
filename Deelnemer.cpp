#include "Deelnemer.h"

// constructors
Deelnemer::Deelnemer(const Atleet& atleet, int tijd_zwem, int tijd_fiets, int tijd_loop)
    : atleet(atleet),
    tijd_zwem(tijd_zwem),
    tijd_fiets(tijd_fiets),
    tijd_loop(tijd_loop),
    heeft_wissel1(false),
    heeft_wissel2(false),
    tijd_wissel1(0),
    tijd_wissel2(0) {}

Deelnemer::Deelnemer(const Atleet& atleet, int tijd_zwem, int tijd_fiets, int tijd_loop, int tijd_wissel1, int tijd_wissel2)
    : atleet(atleet),
    tijd_zwem(tijd_zwem),
    tijd_fiets(tijd_fiets),
    tijd_loop(tijd_loop),
    heeft_wissel1(true),
    heeft_wissel2(true),
    tijd_wissel1(tijd_wissel1),
    tijd_wissel2(tijd_wissel2) {}

// setters
void Deelnemer::set_tijd_zwem(int nieuwe_tijd_zwem)
{
    tijd_zwem = nieuwe_tijd_zwem;
}

void Deelnemer::set_tijd_fiets(int nieuwe_tijd_fiets)
{
    tijd_fiets = nieuwe_tijd_fiets;
}

void Deelnemer::set_tijd_loop(int nieuwe_tijd_loop)
{
    tijd_loop = nieuwe_tijd_loop;
}

void Deelnemer::set_wisseltijd1(int nieuwe_tijd_wissel1)
{
    tijd_wissel1 = nieuwe_tijd_wissel1; heeft_wissel1 = true;
}

void Deelnemer::set_wisseltijd2(int nieuwe_tijd_wissel2)
{
    tijd_wissel2 = nieuwe_tijd_wissel2; heeft_wissel2 = true;
}

// getters
const Atleet& Deelnemer::get_atleet() const
{
    return atleet;
}

int Deelnemer::get_tijd_zwem() const
{
    return tijd_zwem;
}

int Deelnemer::get_tijd_fiets() const
{
    return tijd_fiets;
}

int Deelnemer::get_tijd_loop() const
{
    return tijd_loop;
}

bool Deelnemer::get_heeft_wissel1() const
{
    return heeft_wissel1;
}

bool Deelnemer::get_heeft_wissel2() const
{
    return heeft_wissel2;
}

int Deelnemer::get_wisseltijd1() const
{
    return tijd_wissel1;
}

int Deelnemer::get_wisseltijd2() const
{
    return tijd_wissel2;
}

// berekening
int Deelnemer::totale_tijd() const
{
    int totaal = tijd_zwem + tijd_fiets + tijd_loop;
    if (heeft_wissel1) totaal += tijd_wissel1;
    if (heeft_wissel2) totaal += tijd_wissel2;
    return totaal;
}
