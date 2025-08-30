#pragma once
#include <string>

using namespace std;

class Licentie
{
private:
	int licentie_nummer;
	string geldig_tot; // Datum voor waarop de licentie geldig is
	string type; // Daglicentie/ trainingslicentie of wedstrijdlicentie

public:
	//Constructor
	Licentie();
	Licentie(int nummer, const string& geldig_tot, const string& type);

	//Getters
	int get_nummer() const;
	string get_geldig_tot() const;
	string get_type() const;

	//Setters
	void set_nummer(int nummer);
	void set_geldig_tot(const string& geldig_tot);
	void set_type(const string& nieuw_type);

};

