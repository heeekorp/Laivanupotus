#include "stdafx.h"
#include "Pelaaja.h"


Pelaaja::Pelaaja()
{
	Nayta_laivat = true;
}

Pelaaja::~Pelaaja()
{
}

void Pelaaja::kysy_siirto(Kentta* Tietokone){
	// Kysyt‰‰n pelaajan laukauksen koordinaatit.

	// Alustetaan muutujat.
	int Laiva_x = 0, Laiva_y = 0;
	char x[1] = "";
	bool Koordinaatit_ok = false;

	// Kysyt‰‰n kunnes k‰ytt‰j‰ antaa hyv‰ksytt‰v‰t koordinaatit.
	while (Koordinaatit_ok == false){
		cout << "Anna X (A-J):";
		cin >> x[0];
		if (x[0] == 'A' || x[0] == 'a'){ Laiva_x = 0; }  // Muutetaan kirjaimena saatu x-koordinaatti numeroksi.
		if (x[0] == 'B' || x[0] == 'b'){ Laiva_x = 1; }
		if (x[0] == 'C' || x[0] == 'c'){ Laiva_x = 2; }
		if (x[0] == 'D' || x[0] == 'd'){ Laiva_x = 3; }
		if (x[0] == 'E' || x[0] == 'e'){ Laiva_x = 4; }
		if (x[0] == 'F' || x[0] == 'f'){ Laiva_x = 5; }
		if (x[0] == 'G' || x[0] == 'g'){ Laiva_x = 6; }
		if (x[0] == 'H' || x[0] == 'h'){ Laiva_x = 7; }
		if (x[0] == 'I' || x[0] == 'i'){ Laiva_x = 8; }
		if (x[0] == 'J' || x[0] == 'j'){ Laiva_x = 9; }

		cout << "Anna Y (1-9):";
		cin >> Laiva_y;
		Laiva_y--;

		// Tarkaistetaan pelaajan antamien koordinaattien kelvollisuus.
		Koordinaatit_ok = true;
		if (Tietokone->Ruudukko[Laiva_x][Laiva_y] > 1){ Koordinaatit_ok = false; }// Koordinaattiin on jo ammuttu
		if (Laiva_x < 0 || Laiva_x > 9){ Koordinaatit_ok = false; }	// Virheellinen x
		if (Laiva_y < 0 || Laiva_y > 9){ Koordinaatit_ok = false; }	// Virheellinen y

		if (Koordinaatit_ok == true) { break; } // Poistutaan silmukasta.
		
	}
	
	system("CLS");

	// P‰ivtet‰‰n pelaajan laukaus tietokoneen ruudukoon.
	if (Tietokone->Ruudukko[Laiva_x][Laiva_y] == 0) { // 0 = laiva
		Tietokone->Ruudukko[Laiva_x][Laiva_y] = 2;  // P‰ivitet‰‰n ohi mennyt laukaus = 2
		cout << "Pelaajan laukaus ohi!" << endl;
	}
	if (Tietokone->Ruudukko[Laiva_x][Laiva_y] == 1) { // 1 = laiva
		Tietokone->Ruudukko[Laiva_x][Laiva_y] = 3;  // P‰ivitet‰‰n osuma laivaan = 3
		cout << "Pelaajan laukaus osui!" << endl;
	}

}

