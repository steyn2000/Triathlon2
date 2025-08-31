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
    bool heeft_wissel1{ false };
    bool heeft_wissel2{ false };
    int tijd_wissel1{ 0 };   // optioneel (alleen gebruiken als heeft_wissel1 == true)
    int tijd_wissel2{ 0 };   // optioneel (alleen gebruiken als heeft_wissel2 == true)

public:
    // constructors
    Deelnemer() = default;
    Deelnemer(const Atleet& atleet, int tijd_zwem, int tijd_fiets, int tijd_loop);
    Deelnemer(const Atleet& atleet, int tijd_zwem, int tijd_fiets, int tijd_loop, int tijd_wissel1, int tijd_wissel2);


    // setters
    void set_tijd_zwem(int nieuwe_tijd_zwem);
    void set_tijd_fiets(int nieuwe_tijd_fiets);
    void set_tijd_loop(int nieuwe_tijd_loop);
    void set_wisseltijd1(int tijd_wissel1);   // zet automatisch heeft_wissel1 = true
    void set_wisseltijd2(int tijd_wissel2);   // zet automatisch heeft_wissel2 = true

    // getters
    const Atleet& get_atleet() const;
    int  get_tijd_zwem() const;
    int  get_tijd_fiets() const;
    int  get_tijd_loop() const;
    bool get_heeft_wissel1() const;
    bool get_heeft_wissel2() const;
    int  get_wisseltijd1() const;
    int  get_wisseltijd2() const;

    // berekening
    int totale_tijd() const;   // som van alle onderdelen (+ wisseltijden als aanwezig)
};
