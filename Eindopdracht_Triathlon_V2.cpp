// Eindopdracht_Triathlon_V2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <map>
#include <fstream>
#include "Atleet.h"
#include "Deelnemer.h"
#include "Wedstrijd.h"
#include "Licentie.h"

using namespace std;

vector<Atleet> atleten;
vector<Wedstrijd> wedstrijden;

const string DATA_BESTAND = "triathlon_data.txt";

void save_data()
{
    ofstream bestand(DATA_BESTAND);
    if (!bestand) return;

    bestand << atleten.size() << '\n';
    for (const auto& atleet : atleten)
    {
        const Licentie& licentie = atleet.get_licentie();
        bestand << atleet.get_voornaam() << '\n'
            << atleet.get_achternaam() << '\n'
            << atleet.get_geboortedatum() << '\n'
            << atleet.get_geslacht() << '\n'
            << licentie.get_nummer() << '\n'
            << licentie.get_geldig_tot() << '\n'
            << licentie.get_type() << '\n';
    }

    bestand << wedstrijden.size() << '\n';
    for (const auto& wedstrijd : wedstrijden)
    {
        bestand << wedstrijd.get_naam() << '\n'
            << wedstrijd.get_datum() << '\n'
            << wedstrijd.get_is_nk() << '\n'
            << wedstrijd.get_met_wissels() << '\n';

        const auto& deelnemers = wedstrijd.get_deelnemers();
        bestand << deelnemers.size() << '\n';
        for (const auto& deelnemer : deelnemers)
        {
            const Atleet& atleet = deelnemer.get_atleet();
            const Licentie& licentie = atleet.get_licentie();
            bestand << atleet.get_voornaam() << '\n'
                << atleet.get_achternaam() << '\n'
                << atleet.get_geboortedatum() << '\n'
                << atleet.get_geslacht() << '\n'
                << licentie.get_nummer() << '\n'
                << licentie.get_geldig_tot() << '\n'
                << licentie.get_type() << '\n';

            bestand << deelnemer.get_tijd_zwem() << ' '
                << deelnemer.get_tijd_fiets() << ' '
                << deelnemer.get_tijd_loop() << ' '
                << deelnemer.get_heeft_wissel1() << ' '
                << deelnemer.get_wisseltijd1() << ' '
                << deelnemer.get_heeft_wissel2() << ' '
                << deelnemer.get_wisseltijd2() << '\n';
        }
    }
}

void load_data()
{
    ifstream in(DATA_BESTAND);
    if (!in) return;

    size_t aantal_atleten;
    if (!(in >> aantal_atleten)) return;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t i = 0; i < aantal_atleten; ++i)
    {
        string voornaam, achternaam, geboortedatum;
        getline(in, voornaam);
        getline(in, achternaam);
        getline(in, geboortedatum);
        char geslacht;
        in >> geslacht;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        int licentienummer;
        string licentie_geldig_tot, licentie_type;
        in >> licentienummer;
        in.ignore();
        getline(in, licentie_geldig_tot);
        getline(in, licentie_type);

        Atleet nieuwe_atleet(voornaam, achternaam, geboortedatum, geslacht);
        nieuwe_atleet.set_licentie(Licentie(licentienummer, licentie_geldig_tot, licentie_type));
        atleten.push_back(nieuwe_atleet);
    }

    size_t aantal_wedstrijden;
    in >> aantal_wedstrijden;
    in.ignore(numeric_limits<streamsize>::max(), '\n');
    for (size_t i = 0; i < aantal_wedstrijden; ++i)
    {
        string naam, datum;
        getline(in, naam);
        getline(in, datum);
        int is_nk_int, met_wissels_int;
        in >> is_nk_int >> met_wissels_int;
        in.ignore(numeric_limits<streamsize>::max(), '\n');

        Wedstrijd wedstrijd(naam, datum, is_nk_int != 0, met_wissels_int != 0);

        size_t aantal_deelnemers;
        in >> aantal_deelnemers;
        in.ignore(numeric_limits<streamsize>::max(), '\n');
        for (size_t j = 0; j < aantal_deelnemers; ++j)
        {
            string voornaam, achternaam, geboortedatum;
            getline(in, voornaam);
            getline(in, achternaam);
            getline(in, geboortedatum);
            char geslacht;
            in >> geslacht;
            in.ignore(numeric_limits<streamsize>::max(), '\n');

            int licentienummer;
            string licentie_geldig_tot, licentie_type;
            in >> licentienummer;
            in.ignore();
            getline(in, licentie_geldig_tot);
            getline(in, licentie_type);

            Atleet atleet(voornaam, achternaam, geboortedatum, geslacht);
            atleet.set_licentie(Licentie(licentienummer, licentie_geldig_tot, licentie_type));

            int tijd_zwem, tijd_fiets, tijd_loop, heeft_wissel1, tijd_wissel1, heeft_wissel2, tijd_wissel2;
            in >> tijd_zwem >> tijd_fiets >> tijd_loop >> heeft_wissel1 >> tijd_wissel1 >> heeft_wissel2 >> tijd_wissel2;
            in.ignore(numeric_limits<streamsize>::max(), '\n');

            Deelnemer deelnemer(atleet, tijd_zwem, tijd_fiets, tijd_loop);
            if (heeft_wissel1) deelnemer.set_wisseltijd1(tijd_wissel1);
            if (heeft_wissel2) deelnemer.set_wisseltijd2(tijd_wissel2);
            wedstrijd.voeg_deelnemer_toe(deelnemer);
        }

        wedstrijden.push_back(wedstrijd);
    }
}

void print_welkom() 
{
    cout << "~~ Welkom bij het Triathlon organisatiesysteem! ~~\n";
}

void print_keuzemenu() 
{
    cout << "\nMaak een keuze:\n";
    cout << "1. Wedstrijd aanmaken\n";
    cout << "2. Toon alle wedstrijden\n";
    cout << "3. Atleet aanmaken\n";
    cout << "4. Toon alle atleten\n";
    cout << "5. Deelnemer (atleet) inschrijven bij wedstrijd\n";
    cout << "6. Aantal deelnemers tonen\n";
    cout << "7. Licentie aan atleet koppelen\n";
    cout << "8. Uitslagen tonen\n";
    cout << "9. Stoppen\n> ";
}

// datum helpers voor "dd-mm-jjjj"
static int get_dag(const string& datum) 
{
    return stoi(datum.substr(0, 2));
}
static int get_maand(const string& datum) 
{
    return stoi(datum.substr(3, 2));
}
static int get_jaar(const string& datum) 
{
    return stoi(datum.substr(6, 4)); 
}

int leeftijd_op_datum(const string& geboortedatum, const string& datum)
{
    int geboortedatum_dag = get_dag(geboortedatum), geboortedatum_maand = get_maand(geboortedatum), geboortedatum_jaar = get_jaar(geboortedatum);
    int datum_dag = get_dag(datum), datum_maand = get_maand(datum), datum_jaar = get_jaar(datum);
    int leeftijd = datum_jaar - geboortedatum_jaar;
    if (datum_maand < geboortedatum_maand || (datum_maand == geboortedatum_maand && datum_dag < geboortedatum_dag)) leeftijd -= 1; // verjaardag nog niet geweest
    return leeftijd;
}

// categorieën volgens jouw eisen
string categorie_van_leeftijd(int leeftijd) 
{
    if (leeftijd < 13)       
        return "<13";
    else if (leeftijd < 18)  
        return "13-17";
    else if (leeftijd <= 35) 
        return "18-35";
    else if (leeftijd <= 45) 
        return "36-45";
    else if (leeftijd <= 55) 
        return "46-55";
    else if (leeftijd <= 65) 
        return "56-65";
    else              
        return "66+";
}

string categorie_van(const Atleet& atleet, const string& wedstrijddatum)
{
    return categorie_van_leeftijd(leeftijd_op_datum(atleet.get_geboortedatum(), wedstrijddatum));
}

int kies_index(int max_index, const string& prompt)
{
    int index;
    cout << prompt;
    cin >> index;

    if (index < 0 || index >= max_index)
    {
        return -1;
    }
    return index;
}

void lijst_atleten(const vector<Atleet>& lijst_atleten)
{
    if (lijst_atleten.empty())
    {
        cout << "Geen atleten.\n";
        return;
    }

    for (size_t i = 0; i < lijst_atleten.size(); ++i)
    {
        const Licentie& licentie = lijst_atleten[i].get_licentie();
        cout << "[" << i << "] "
            << lijst_atleten[i].get_voornaam() << " " << lijst_atleten[i].get_achternaam() << " | Geb.datum: " << lijst_atleten[i].get_geboortedatum() << " | Geslacht: "
            << lijst_atleten[i].get_geslacht() << " | Licentie: " << licentie.get_type() << " (" << licentie.get_nummer() << ")\n";
    }
}

void lijst_wedstrijden(const vector<Wedstrijd>& lijst_wedstrijden)
{
    if (lijst_wedstrijden.empty())
    {
        cout << "Geen wedstrijden.\n";
        return;
    }

    for (size_t i = 0; i < lijst_wedstrijden.size(); ++i)
    {
        cout << "[" << i << "] " << lijst_wedstrijden[i].get_naam() << " (" << lijst_wedstrijden[i].get_datum() << ")\n";
    }
}

Atleet invoer_atleet() 
{
    string voornaam, achternaam, geboortedatum;
    char geslacht;

    cout << "Voornaam: ";
    cin >> voornaam;
    cout << "Achternaam: ";
    cin >> achternaam;
    cout << "Geboortedatum (dd-mm-jjjj): ";
    cin >> geboortedatum;
    cout << "Geslacht (M/V): ";
    cin >> geslacht;

    return Atleet(voornaam, achternaam, geboortedatum, geslacht);
}
// functie voor het formatteren van de tijd
string format_tijd(int seconden)
{
    int uren = seconden / 3600;
    int minuten = (seconden % 3600) / 60;
    int resterende_seconden = seconden % 60;
    return to_string(uren) + "u " + to_string(minuten) + "m " + to_string(resterende_seconden) + "s";
}

// Functie voor het tonen van de uitslagen
void toon_uitslag_van_wedstrijd(const vector<Wedstrijd>& wedstrijden) 
{
    if (wedstrijden.empty()) 
    {
        cout << "Geen wedstrijden.\n";
        return;
    }

    lijst_wedstrijden(wedstrijden);
    int wedstrijd_index = kies_index((int)wedstrijden.size(), "Kies wedstrijd-index: ");
    if (wedstrijd_index == -1) 
    {
        cout << "Ongeldige keuze.\n";
        return;
    }

    const Wedstrijd& wedstrijd = wedstrijden[wedstrijd_index];
    auto uitslag = wedstrijd.deelnemer_lijst_gesorteerd(); // gesorteerd op totale tijd
    if (uitslag.empty()) 
    {
        cout << "Geen deelnemers voor deze wedstrijd.\n";
        return;
    }

    bool met_wissels = wedstrijd.get_met_wissels();

    // --------- TOTAAL ---------
    cout << "\nUitslag: " << wedstrijd.get_naam() << " (" << wedstrijd.get_datum() << ")\n";
    cout << "Pos  Naam                     Zwem       ";

    if (met_wissels)
        cout << "T1         ";
    cout << "Fiets      ";

    if (met_wissels)
        cout << "T2         ";
    cout << "Loop       Totaal\n";
    cout << "---- -----------------------  ----------  ";

    if (met_wissels)
        cout << "----------  ";
    cout << "----------  ";

    if (met_wissels)
        cout << "----------  ";
    cout << "----------  ----------\n";

    for (size_t i = 0; i < uitslag.size(); ++i) 
    {
        const Deelnemer& deelnemer = uitslag[i];
        const Atleet& atleet = deelnemer.get_atleet();
        string naam = atleet.get_voornaam() + " " + atleet.get_achternaam();

        if (naam.size() > 23) naam = naam.substr(0, 23);
            cout << (i + 1);

        if (i + 1 < 10) 
            cout << "   ";

        else 
            cout << "  ";
            cout << naam;

        if (naam.size() < 23)
            cout << string(23 - naam.size(), ' ');
        cout << "    " << format_tijd(deelnemer.get_tijd_zwem());

        if (met_wissels)
            cout << "    " << format_tijd(deelnemer.get_wisseltijd1());
        cout << "    " << format_tijd(deelnemer.get_tijd_fiets());

        if (met_wissels)
            cout << "    " << format_tijd(deelnemer.get_wisseltijd2());
        cout << "    " << format_tijd(deelnemer.get_tijd_loop());
        cout << "    " << format_tijd(deelnemer.totale_tijd()) << "\n";
    }

    // --------- PER CATEGORIE ---------
    // groepeert deelnemers per categorie
    map<string, vector<Deelnemer>> groepen;
    for (const auto& deelnemer : uitslag)
    {
        const Atleet& atleet = deelnemer.get_atleet();
        string categorie = categorie_van(atleet, wedstrijd.get_datum());
        groepen[categorie].push_back(deelnemer);
    }

    vector<string> categorie_volgorde = { "<13","13-17","18-35","36-45","46-55","56-65","66+" };

    for (const auto& categorie : categorie_volgorde)
    {
        auto it = groepen.find(categorie);
        if (it == groepen.end() || it->second.empty()) continue;

        auto& categorie_deelnemers = it->second; // al gesorteerd door kopie uit 'uitslag', maar safe nog eens:
        sort(categorie_deelnemers.begin(), categorie_deelnemers.end(),
                  [](const Deelnemer& e1, const Deelnemer& e2){ return e1.totale_tijd() < e2.totale_tijd(); });

        cout << "\n[" << categorie << "]\n";
        cout << "Pos  Naam                             Zwem       ";

        if (met_wissels)
            cout << "T1         ";
        cout << "Fiets      ";

        if (met_wissels)
            cout << "T2         ";
        cout << "Loop       Totaal\n";
        cout << "---- --------------------------------  ---------  ";

        if (met_wissels)
            cout << "---------  ";
        cout << "---------  ";

        if (met_wissels)
            cout << "---------  ";
        cout << "---------  ---------\n";

        for (size_t i = 0; i < categorie_deelnemers.size(); ++i) {
            const Deelnemer& deelnemer = categorie_deelnemers[i];
            const Atleet& atleet = deelnemer.get_atleet();
            string naam = atleet.get_voornaam() + " " + atleet.get_achternaam();
            if (naam.size() > 32) naam = naam.substr(0, 32);
            cout << (i + 1);

            if (i + 1 < 10)
                cout << "   ";
            else
                cout << "  ";
            cout << naam;

            if (naam.size() < 32) cout << string(32 - naam.size(), ' ');
            cout << "  " << format_tijd(deelnemer.get_tijd_zwem());

            if (met_wissels)
                cout << "   " << format_tijd(deelnemer.get_wisseltijd1());
            cout << "   " << format_tijd(deelnemer.get_tijd_fiets());
            if (met_wissels)
                cout << "   " << format_tijd(deelnemer.get_wisseltijd2());
            cout << "   " << format_tijd(deelnemer.get_tijd_loop());
            cout << "   " << format_tijd(deelnemer.totale_tijd()) << "\n";
        }
    }
    cout << endl;
}

int main() {
    load_data();
    print_welkom();

    bool doorgaan = true;
    while (doorgaan) 
    {
        print_keuzemenu();
        int keuze;
        cin >> keuze;

        if (keuze == 1)
        {
            string naam, datum;
            string is_nk_keuze, wissels_keuze;

            cout << "Naam wedstrijd: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, naam);

            cout << "Datum (bv. 15-06-2024): ";
            getline(cin, datum);

            cout << "Is NK? (ja/nee): ";
            cin >> is_nk_keuze;

            cout << "Wisseltijden registreren? (ja/nee): ";
            cin >> wissels_keuze;

            bool is_nk = (is_nk_keuze == "ja");
            bool heeft_wissels = (wissels_keuze == "ja");

            // nieuw object maken en toevoegen aan de vector
            Wedstrijd nieuwe_wedstrijd(naam, datum, is_nk, heeft_wissels);
            wedstrijden.push_back(nieuwe_wedstrijd);

            cout << "Wedstrijd aangemaakt met index ["
                << (int)wedstrijden.size() - 1 << "].\n";
        }

        else if (keuze == 2) 
        {
            lijst_wedstrijden(wedstrijden);
        }

        else if (keuze == 3) 
        {
            Atleet atleet = invoer_atleet();
            atleten.push_back(atleet);
            cout << "Atleet aangemaakt met index [" << (int)atleten.size() - 1 << "].\n";
        }

        else if (keuze == 4) 
        {
            lijst_atleten(atleten);
        }

        else if (keuze == 5)
        {
            if (wedstrijden.empty())
            {
                cout << "Geen wedstrijden. Maak eerst een wedstrijd (optie 1).\n";
            }
            else if (atleten.empty()) 
            {
                cout << "Geen atleten. Maak eerst een atleet (optie 2).\n";
            }
            else 
            {
                lijst_wedstrijden(wedstrijden);
                int wedstrijd_index = kies_index((int)wedstrijden.size(), "Kies wedstrijd-index: ");
                if (wedstrijd_index == -1)
                {
                    cout << "Ongeldige keuze.\n";
                }
                else {
                    lijst_atleten(atleten);
                    int atleet_index = kies_index((int)atleten.size(), "Kies atleet-index: ");
                    if (atleet_index == -1) 
                    {
                        cout << "Ongeldige keuze.\n";
                    }
                    else 
                    {
                        // NK-licentiecontrole
                        if (wedstrijden[wedstrijd_index].get_is_nk())
                        {
                            string licentie_type = atleten[atleet_index].get_licentie().get_type();
                            if (licentie_type != "Wedstrijdlicentie") {
                                cout << "Deze wedstrijd is een NK, atleet heeft geen Wedstrijdlicentie.\n";
                                cout << "Koppel eerst een Wedstrijdlicentie via optie 7 en probeer opnieuw.\n";
                                continue; // ga terug naar het hoofdmenu (while-loop)
                            }
                        }

                        int tijd_zwem, tijd_fiets, tijd_loop;
                        cout << "Tijden in seconden.\n";
                        cout << "Zwem: ";
                        cin >> tijd_zwem;
                        cout << "Fiets: ";
                        cin >> tijd_fiets;
                        cout << "Loop: ";
                        cin >> tijd_loop;

                        if (wedstrijden[wedstrijd_index].get_met_wissels())
                        {
                            int tijd_wissel1, tijd_wissel2;
                            cout << "T1 (wissel zwemmen->fietsen, sec): ";
                            cin >> tijd_wissel1;
                            cout << "T2 (wissel fietsen->lopen, sec):   ";
                            cin >> tijd_wissel2;

                            Deelnemer deelnemer(atleten[atleet_index], tijd_zwem, tijd_fiets, tijd_loop, tijd_wissel1, tijd_wissel2);
                            wedstrijden[wedstrijd_index].voeg_deelnemer_toe(deelnemer);
                        }
                        else {
                            Deelnemer deelnemer(atleten[atleet_index], tijd_zwem, tijd_fiets, tijd_loop);
                            wedstrijden[wedstrijd_index].voeg_deelnemer_toe(deelnemer);
                        }

                        cout << "Deelnemer ingeschreven bij wedstrijd [" << wedstrijd_index << "].\n";
                    }
                }
            }
        }
        
        else if (keuze == 6) 
        {
            if (wedstrijden.empty()) {
                cout << "Geen wedstrijden.\n";
            }
            else {
                lijst_wedstrijden(wedstrijden);
                int wedstrijd_index = kies_index((int)wedstrijden.size(), "Kies wedstrijd-index: ");
                if (wedstrijd_index == -1) {
                    cout << "Ongeldige keuze.\n";
                }
                else {
                    cout << "Aantal deelnemers: "
                        << wedstrijden[wedstrijd_index].aantal_deelnemers() << "\n";
                }
            }
        }

        else if (keuze == 7) 
        {
            if (atleten.empty()) {
                cout << "Geen atleten.\n";
            }
            else {
                lijst_atleten(atleten);
                int atleet_index = kies_index((int)atleten.size(), "Kies atleet-index: ");
                if (atleet_index == -1) 
                {
                    cout << "Ongeldige keuze.\n";
                }
                else {
                    int keuze_licentie;
                    cout << "Kies licentie (1 = Dag, 2 = Trainings, 3 = Wedstrijd): ";
                    cin >> keuze_licentie;

                    int licentienummer;
                    string geldig_tot;
                    cout << "Licentienummer: ";
                    cin >> licentienummer;
                    cout << "Geldig tot (bv. 31-12-2024): ";
                    cin >> geldig_tot;

                    string licentie_type = "Daglicentie";
                    if (keuze_licentie == 2) licentie_type = "Trainingslicentie";
                    else if (keuze_licentie == 3) licentie_type = "Wedstrijdlicentie";

                    Licentie licentie(licentienummer, geldig_tot, licentie_type);
                    atleten[atleet_index].set_licentie(licentie);
                    cout << "Licentie gekoppeld aan atleet [" << atleet_index << "].\n";
                }
            }

        }

        else if (keuze == 8)
        {
            toon_uitslag_van_wedstrijd(wedstrijden);
        }

        else if (keuze == 9) 
        {
            doorgaan = false;
        }

        else 
        {
            cout << "Ongeldige keuze\n";
        }
    }

    save_data();
    cout << "Tot ziens!\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
