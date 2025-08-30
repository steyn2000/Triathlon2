#include "Deelnemer.h"

// constructors
Deelnemer::Deelnemer(const Atleet& atleet, int tijd_zwem, int tijd_fiets, int tijd_loop)
    : atleet(atleet),
    tijd_zwem(tijd_zwem),
    tijd_fiets(tijd_fiets),
    tijd_loop(tijd_loop),
    heeft_t1(false),
    heeft_t2(false),
    t1(0),
    t2(0) {}

Deelnemer::Deelnemer(const Atleet& atleet, int tijd_zwem, int tijd_fiets, int tijd_loop, int tijd_t1, int tijd_t2)
    : atleet(atleet),
    tijd_zwem(tijd_zwem),
    tijd_fiets(tijd_fiets),
    tijd_loop(tijd_loop),
    heeft_t1(true),
    heeft_t2(true),
    t1(tijd_t1),
    t2(tijd_t2) {}

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

void Deelnemer::set_t1(int nieuwe_t1)
{
    t1 = nieuwe_t1; heeft_t1 = true;
}

void Deelnemer::set_t2(int nieuwe_t2)
{
    t2 = nieuwe_t2; heeft_t2 = true;
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

bool Deelnemer::get_heeft_t1() const
{
    return heeft_t1;
}

bool Deelnemer::get_heeft_t2() const
{
    return heeft_t2;
}

int Deelnemer::get_t1() const
{
    return t1;
}

int Deelnemer::get_t2() const
{
    return t2;
}

// berekening
int Deelnemer::totale_tijd() const
{
    int totaal = tijd_zwem + tijd_fiets + tijd_loop;
    if (heeft_t1) totaal += t1;
    if (heeft_t2) totaal += t2;
    return totaal;
}
