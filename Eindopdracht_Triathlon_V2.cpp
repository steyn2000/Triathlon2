// Eindopdracht_Triathlon_V2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <vector>
#include <limits>  
#include <algorithm>
#include <map>
#include "Atleet.h"
#include "Deelnemer.h"
#include "Wedstrijd.h"
#include "Licentie.h"

using namespace std;

vector<Atleet> atleten;
vector<Wedstrijd> wedstrijden;

void print_welkom() {
    cout << "~~ Welkom bij het Triathlon organisatiesysteem! ~~\n";
}

void print_keuzemenu() {
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

int leeftijd_op_datum(const string& geboortedatum, const string& datum) {
    int gb_d = get_dag(geboortedatum), gb_m = get_maand(geboortedatum), gb_j = get_jaar(geboortedatum);
    int wd_d = get_dag(datum), wd_m = get_maand(datum), wd_j = get_jaar(datum);
    int leeftijd = wd_j - gb_j;
    if (wd_m < gb_m || (wd_m == gb_m && wd_d < gb_d)) leeftijd -= 1; // verjaardag nog niet geweest
    return leeftijd;
}

// categorie�n volgens jouw eisen
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
    int i;
    cout << prompt;
    cin >> i;

    if (i < 0 || i >= max_index)
    {
        return -1;
    }
    return i;
}

void lijst_atleten(const vector<Atleet>& lijst)
{
    if (lijst.empty())
    {
        cout << "Geen atleten.\n";
        return;
    }

    for (size_t i = 0; i < lijst.size(); ++i)
    {
        cout << "[" << i << "] "
            << lijst[i].get_voornaam() << " " << lijst[i].get_achternaam() << " | Geb.datum: " << lijst[i].get_geboortedatum() << " | Geslacht: " 
            << lijst[i].get_geslacht() << " | Licentie: " << lijst[i].get_licentie().get_type() << "\n";
    }
}

void lijst_wedstrijden(const vector<Wedstrijd>& lijst)
{
    if (lijst.empty())
    {
        cout << "Geen wedstrijden.\n";
        return;
    }

    for (size_t i = 0; i < lijst.size(); ++i)
    {
        cout << "[" << i << "] " << lijst[i].get_naam() << " (" << lijst[i].get_datum() << ")\n";
    }
}

Atleet invoer_atleet() {
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
    int sec = seconden % 60;
    return to_string(uren) + "u " + to_string(minuten) + "m " + to_string(sec) + "s";
}

// Functie voor het tonen van de uitslagen
void toon_uitslag_van_wedstrijd(const std::vector<Wedstrijd>& wedstrijden) {
    if (wedstrijden.empty()) 
    {
        cout << "Geen wedstrijden.\n";
        return;
    }

    lijst_wedstrijden(wedstrijden);
    int wi = kies_index((int)wedstrijden.size(), "Kies wedstrijd-index: ");
    if (wi == -1) 
    {
        cout << "Ongeldige keuze.\n";
        return;
    }

    const Wedstrijd& wedstrijd= wedstrijden[wi];
    auto uitslag = wedstrijd.deelnemer_lijst_gesorteerd(); // gesorteerd op totale tijd
    if (uitslag.empty()) 
    {
        std::cout << "Geen deelnemers voor deze wedstrijd.\n";
        return;
    }

    bool met_wissels = wedstrijd.get_met_wissels();

    // --------- TOTAAL ---------
    std::cout << "\nUitslag: " << wedstrijd.get_naam() << " (" << wedstrijd.get_datum() << ")\n";
    std::cout << "Pos  Naam                     Zwem       ";
    if (met_wissels) std::cout << "T1         ";
    std::cout << "Fiets      ";
    if (met_wissels) std::cout << "T2         ";
    std::cout << "Loop       Totaal\n";

    std::cout << "---- -----------------------  ---------  ";
    if (met_wissels) std::cout << "---------  ";
    std::cout << "---------  ";
    if (met_wissels) std::cout << "---------  ";
    std::cout << "---------  ---------\n";

    for (size_t i = 0; i < uitslag.size(); ++i) {
        const Deelnemer& deelnemer = uitslag[i];
        const Atleet& atleet = deelnemer.get_atleet();
        std::string naam = atleet.get_voornaam() + " " + atleet.get_achternaam();
        if (naam.size() > 23) naam = naam.substr(0, 23);

        std::cout << (i + 1);
        if (i + 1 < 10) std::cout << "   "; else std::cout << "  ";

        std::cout << naam;
        if (naam.size() < 23) std::cout << std::string(23 - naam.size(), ' ');

        std::cout << "   " << format_tijd(deelnemer.get_tijd_zwem());
        if (met_wissels) std::cout << "   " << format_tijd(deelnemer.get_t1());
        std::cout << "   " << format_tijd(deelnemer.get_tijd_fiets());
        if (met_wissels) std::cout << "   " << format_tijd(deelnemer.get_t2());
        std::cout << "   " << format_tijd(deelnemer.get_tijd_loop());
        std::cout << "   " << format_tijd(deelnemer.totale_tijd()) << "\n";
    }

    // --------- PER CATEGORIE ---------
    // groepeer deelnemers per categorie
    std::map<std::string, std::vector<Deelnemer>> groepen;
    for (const auto& d : uitslag) {
        const Atleet& a = d.get_atleet();
        std::string cat = categorie_van(a, wedstrijd.get_datum());
        groepen[cat].push_back(d);
    }

    std::vector<std::string> volgorde = { "<13","13-17","18-35","36-45","46-55","56-65","66+" };

    for (const auto& cat : volgorde) {
        auto it = groepen.find(cat);
        if (it == groepen.end() || it->second.empty()) continue;

        auto& lijst = it->second; // al gesorteerd door kopie uit 'uitslag', maar safe nog eens:
        std::sort(lijst.begin(), lijst.end(),
                  [](const Deelnemer& e1, const Deelnemer& e2){ return e1.totale_tijd() < e2.totale_tijd(); });

        std::cout << "\n[" << cat << "]\n";
        std::cout << "Pos  Naam                             Zwem       ";
        if (met_wissels) std::cout << "T1         ";
        std::cout << "Fiets      ";
        if (met_wissels) std::cout << "T2         ";
        std::cout << "Loop       Totaal\n";

        std::cout << "---- --------------------------------  ---------  ";
        if (met_wissels) std::cout << "---------  ";
        std::cout << "---------  ";
        if (met_wissels) std::cout << "---------  ";
        std::cout << "---------  ---------\n";

        for (size_t i = 0; i < lijst.size(); ++i) {
            const Deelnemer& deelnemer = lijst[i];
            const Atleet& atleet = deelnemer.get_atleet();
            std::string naam = atleet.get_voornaam() + " " + atleet.get_achternaam();
            if (naam.size() > 32) naam = naam.substr(0, 32);

            std::cout << (i + 1);
            if (i + 1 < 10) std::cout << "   "; else std::cout << "  ";

            std::cout << naam;
            if (naam.size() < 32) std::cout << std::string(32 - naam.size(), ' ');

            std::cout << "  " << format_tijd(deelnemer.get_tijd_zwem());
            if (met_wissels) std::cout << "   " << format_tijd(deelnemer.get_t1());
            std::cout << "   " << format_tijd(deelnemer.get_tijd_fiets());
            if (met_wissels) std::cout << "   " << format_tijd(deelnemer.get_t2());
            std::cout << "   " << format_tijd(deelnemer.get_tijd_loop());
            std::cout << "   " << format_tijd(deelnemer.totale_tijd()) << "\n";
        }
    }

    std::cout << std::endl;
}

int main() {
    print_welkom();

    bool heeft_atleet = false;
    Atleet laatst_atleet;

    bool doorgaan = true;
    while (doorgaan) 
    {
        print_keuzemenu();
        int keuze;
        cin >> keuze;

        if (keuze == 1) 
        {
            string naam, datum;
            int nk, wissels;

            cout << "Naam wedstrijd: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, naam);

            cout << "Datum (bv. 15-06-2024): ";
            getline(cin, datum);

            cout << "Is NK? (0/1): ";
            cin >> nk;

            cout << "Wisseltijden registreren? (0/1): ";
            cin >> wissels;

            // nieuw object maken en toevoegen aan de vector
            Wedstrijd nieuw(naam, datum, nk != 0, wissels != 0);
            wedstrijden.push_back(nieuw);

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
                            string lic_type = atleten[atleet_index].get_licentie().get_type();
                            if (lic_type != "Wedstrijdlicentie") {
                                cout << "Deze wedstrijd is een NK, atleet heeft geen Wedstrijdlicentie.\n";
                                cout << "Koppel eerst een Wedstrijdlicentie via optie 7 en probeer opnieuw.\n";
                                continue; // ga terug naar het hoofdmenu (while-loop)
                            }
                        }

                        int tz, tf, tl;
                        cout << "Tijden in seconden.\n";
                        cout << "Zwem: "; 
                        cin >> tz;
                        cout << "Fiets: ";
                        cin >> tf;
                        cout << "Loop: ";
                        cin >> tl;

                        if (wedstrijden[wedstrijd_index].get_met_wissels()) 
                        {
                            int tijd_t1, tijd_t2;
                            cout << "T1 (wissel zwemmen->fietsen, sec): ";
                            cin >> tijd_t1;
                            cout << "T2 (wissel fietsen->lopen, sec):   ";
                            cin >> tijd_t2;

                            Deelnemer deelnemer(atleten[atleet_index], tz, tf, tl, tijd_t1, tijd_t2);
                            wedstrijden[wedstrijd_index].voeg_deelnemer_toe(deelnemer);
                        }
                        else {
                            Deelnemer deelnemer(atleten[atleet_index], tz, tf, tl);
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

                    int nummer;
                    string geldig_tot;
                    cout << "Licentienummer: ";
                    cin >> nummer;
                    cout << "Geldig tot (bv. 31-12-2024): ";
                    cin >> geldig_tot;

                    string licentie_type = "Daglicentie";
                    if (keuze_licentie == 2) licentie_type = "Trainingslicentie";
                    else if (keuze_licentie == 3) licentie_type = "Wedstrijdlicentie";

                    Licentie licentie(nummer, geldig_tot, licentie_type);
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
