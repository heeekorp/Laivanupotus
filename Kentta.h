#pragma once
class Kentta
{
public:
	int Ruudukko[10][10]; // Pelikenttä 2 ulotteisena taulukkona.
	bool Nayta_laivat;	  // Näytetäänkö laivat tulostettaessa kenttä.
	vector<Laiva>Laivat;	//  Laivojen tiedot
	
	void Piirra_taulukko();  // Tulostaa ruudukon sisällön!
	bool Tarkista_laivan_koordinaatit(Laiva); // Tarkistaa laivan koordinaattien laillisuuden.
	void Aseta_laiva_kenttaan(Laiva);  // Asettaa laivan ruudukkoon koordinaattien mukaan. 
	bool tarkista_laivat(vector<Laiva>*); // Tarkistaa onko laiva uponnut, jos on, funktio palauttaa false

	Kentta();
	~Kentta();
};

