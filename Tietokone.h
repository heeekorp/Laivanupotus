#pragma once
class Tietokone : public Kentta // Tietokone luokka peritty kentt‰ luokasta.
{
public:
	int Laukaushistoria;	// M‰‰ritt‰‰ logiikan, jolla tietokoneen siirto generoidaan.  
	int Osuma1_x;			//  Tietokoneen 1. osuman koordinaatit
	int Osuma1_y;
	int Osuma2_x;			//  Tietokoneen 2. osuman koordinaatit
	int Osuma2_y;
	void Arvo_laivan_sijainti(Laiva*);	// Arpoo koordinaatit laivalle.
	void Tietokoneen_siirto(Kentta*);	// Generoi tietokoneen siirron.

	Tietokone();
	~Tietokone();
};

