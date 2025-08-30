#pragma once
#include <string>
#include "Atleet.h"

using namespace std;

class Deelnemer
{
private:
    Atleet atleet;         // kopie van de atleet voor deze inschrijving
    int tijd_zwem{ 0 };      // in seconden
    int tijd_fiets{ 0 };     // in seconden
    int tijd_loop{ 0 };      // in seconden
    bool heeft_t1{ false };
    bool heeft_t2{ false };
    int t1{ 0 };             // optioneel (alleen gebruiken als heeft_t1 == true)
    int t2{ 0 };             // optioneel (alleen gebruiken als heeft_t2 == true)

public:
    // constructors
    Deelnemer() = default;
    Deelnemer(const Atleet& atleet, int tijd_zwem, int tijd_fiets, int tijd_loop);
    Deelnemer(const Atleet& atleet, int tijd_zwem, int tijd_fiets, int tijd_loop, int tijd_t1, int tijd_t2);


    // setters
    void set_tijd_zwem(int nieuwe_tijd_zwem);
    void set_tijd_fiets(int nieuwe_tijd_fiets);
    void set_tijd_loop(int nieuwe_tijd_loop);
    void set_t1(int tijd_t1);   // zet automatisch heeft_t1 = true
    void set_t2(int tijd_t2);   // zet automatisch heeft_t2 = true

    // getters
    const Atleet& get_atleet() const;
    int  get_tijd_zwem() const;
    int  get_tijd_fiets() const;
    int  get_tijd_loop() const;
    bool get_heeft_t1() const;
    bool get_heeft_t2() const;
    int  get_t1() const;
    int  get_t2() const;

    // berekening
    int totale_tijd() const;   // som van alle onderdelen (+ t1/t2 als aanwezig)
};
