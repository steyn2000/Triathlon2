#pragma once
#include <string>
#include <vector>

using namespace std;

struct DopingControle
{
    string datum;               // datum van de controle
    bool doping_geconstateerd;  // true als er doping is geconstateerd
};

class Licentie
{
private:
        int licentie_nummer;
        string geldig_tot; // Datum voor waarop de licentie geldig is
        string type; // Daglicentie/ trainingslicentie of wedstrijdlicentie
        string vereniging; // alleen relevant voor trainingslicentie
        vector<DopingControle> doping_controles; // alleen voor wedstrijdlicentie

public:
        //Constructor
        Licentie();
        Licentie(int nummer, const string& geldig_tot, const string& type, const string& vereniging = "");

        //Getters
        int get_nummer() const;
        string get_geldig_tot() const;
        string get_type() const;
        string get_vereniging() const;
        const vector<DopingControle>& get_doping_controles() const;

        //Setters
        void set_nummer(int nummer);
        void set_geldig_tot(const string& geldig_tot);
        void set_type(const string& nieuw_type);
        void set_vereniging(const string& vereniging);
        void voeg_dopingcontrole_toe(const DopingControle& controle);

};


