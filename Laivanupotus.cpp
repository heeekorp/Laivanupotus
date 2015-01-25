// Laivanupotus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	int Laivajen_koot[LAIVOJEN_MAARA] = {1, 1, 1, 1, 2, 2, 2, 3, 3, 4 }; // Taulukko, jossa laivojen pituudet.
	int Valinta = 0;

	// ��kk�set
	setlocale(LC_ALL, "");

	// Luodaan tietokone ja pelaaja -oliot
	Pelaaja pelaaja;
	Tietokone tietokone;
	
	// Kysyt��n sijoittaako  pelaaja itse laivansa, vai arpooko tietokone ne.
	system("CLS");
	cout << "Laivanupotus:\n" << endl;
	cout << "(1) Sijoita laivat kentt��n k�sin." << endl;
	cout << "(2) Tietokone arpoo laivat." << endl;
	cout << "Valinta:";
	cin >> Valinta;

	switch (Valinta)
	{
	case 1:{
		// Kysyt��n pelaajalta laivojen sijainnit.

		for (int iterator = 0; iterator < LAIVOJEN_MAARA; iterator++){
			// Laiva olio
			Laiva UusiLaiva;

			system("CLS");
			// Piirret��n pelaajan kentt�.
			pelaaja.Piirra_taulukko();

			while (true){
				// Laivan koko taulukosta.
				UusiLaiva.Laiva_koko = Laivajen_koot[iterator];
				// Kysyt��n laivan koordinaatit ja suunta
				UusiLaiva.Lisaa_laiva();

				// Tarkista_laivan_koordinaatit -funktio palauttaa boolean arvona laivan sijainnin kelvollisuuden.
				if (pelaaja.Tarkista_laivan_koordinaatit(UusiLaiva) == true){
					// Jos laivan sijainti ok, asetetaan laiva pelaajan kentt��n...
					pelaaja.Aseta_laiva_kenttaan(UusiLaiva);
					// .. ja lis�t��n laiva olio pelaajanLaivat vektoriin. 
					pelaaja.Laivat.push_back(UusiLaiva);
					// Pois while silmukasta.
					break;
				} // if
				else { cout << "Laivan sijainti virheellinen!" << endl; }; // Jos laivan koordinaatit virheelliset...

			}// while
		}// for
	}
	case 2:{
		// Generoidaan pelaajan laivat automaattisesti
		for (int iterator = 0; iterator < LAIVOJEN_MAARA; iterator++) {
			//Luodaan laiva -olio
			Laiva UusiLaiva;
			// Laivojen koot taulukosta
			UusiLaiva.Laiva_koko = Laivajen_koot[iterator];

			while (true){
				// Funktio arpoo laivan koordinaatit, parametrina laiva olio.
				tietokone.Arvo_laivan_sijainti(&UusiLaiva);
				// Tarkastetaan olivatko laivan koordinaatit kelvolliset...
				if (pelaaja.Tarkista_laivan_koordinaatit(UusiLaiva) == true){ break; } // ... jos olivat, poistutaan silmukasta. 
			}
			// Asetetaan laiva pelaajan kentt��n.
			pelaaja.Aseta_laiva_kenttaan(UusiLaiva);
			// ... ja vektoriin.
			pelaaja.Laivat.push_back(UusiLaiva);
		}
	}
	default:
		break;
	} // switch/case p��ttyy.


	// Generoidaan tietokoneen Laivat
	for (int iterator = 0; iterator < LAIVOJEN_MAARA; iterator++) {
		Laiva UusiLaiva;
		UusiLaiva.Laiva_koko = Laivajen_koot[iterator];

		while (true){
			tietokone.Arvo_laivan_sijainti(&UusiLaiva);
			if (tietokone.Tarkista_laivan_koordinaatit(UusiLaiva) == true){ break; }
		}
		// Tietokoneen laivat tietokoneen kentt��n ja vektoriin.
		tietokone.Aseta_laiva_kenttaan(UusiLaiva);
		tietokone.Laivat.push_back(UusiLaiva);
	}
	
	
	///////////////////////////////
	//// Pelisilmukka alkaa! /////
	///////////////////////////////

	system("CLS");
	
	while (true){

		// Tulostetaan j�ljell� olevien laivojen m��r�t vektoreista.
		cout << "\nLaivoja j�ljella:" << endl;
		cout << "Pelaaja:" << pelaaja.Laivat.size() << " Tietokone : " << tietokone.Laivat.size() << endl;
		// Merkkien selitykset
		cout << "Merkit:" << endl;
		cout << "\ + = laiva, / = ohilaukaus\nX = osuma, O = uponnut laiva" << endl;

		//Piirret��n pelaajan ja tietokoneen kent�t.
		cout << "\nPelaajan kentt�:" << endl;;
		pelaaja.Piirra_taulukko();
		cout << "\nTietokoneen kentt�:" << endl;;
		tietokone.Piirra_taulukko();

		// Kysyt��n pelaajan siirto, funktion parametrina tietokone olio, josta tarkastellaan tietokoneen kentt��.
		pelaaja.kysy_siirto(&tietokone); 
		
		// Generoidaan tietokoneen siirto, funktion parametrina pelaaja olio, josta tarkastellaan pelaajan kentt��.
		tietokone.Tietokoneen_siirto(&pelaaja);

		// Tarkista_laivat() palauttaa false, jos jokin laiva on uponnut.
		// Funktio saa parametrina PelaajanLaivat vektorin.
		if (pelaaja.tarkista_laivat(&(pelaaja.Laivat)) == false){ 
			// Jos tietokone upotti laivan, nollataan tietokoneen laukaisuhistoria.
			tietokone.Laukaushistoria = 0;
			cout << "Tietokone upotti laivan!" << endl;
		}

		// Tarkistetaan osuiko pelaaja.
		if (tietokone.tarkista_laivat(&(tietokone.Laivat)) == false){
			cout << "Pelaaja upotti laivan!" << endl;
		}
		
		// Tarkistetaan mahdollinen voittaja!
		// Onko laivoja j�ljell� pelaajan tai tietokoneen laivatvektorissa.
		if (tietokone.Laivat.size() == 0 && pelaaja.Laivat.size() == 0){
			cout << "Tasapeli!" << endl;
			cout << "\nPelaajan kentt�:" << endl;;
			pelaaja.Piirra_taulukko();
			cout << "\nTietokoneen kentt�:" << endl;;
			tietokone.Piirra_taulukko();
			break;
		}
		if (tietokone.Laivat.size() == 0){ 
			cout << "Pelaaja voitti!" << endl;
			cout << "\nPelaajan kentt�:" << endl;;
			pelaaja.Piirra_taulukko();
			cout << "\nTietokoneen kentt�:" << endl;;
			tietokone.Piirra_taulukko();
			break;
		}	
		if (pelaaja.Laivat.size() == 0){
			cout << "Tietokone voitti!" << endl;
			cout << "\nPelaajan kentt�:" << endl;;
			pelaaja.Piirra_taulukko();
			cout << "\nTietokoneen kentt�:" << endl;;
			tietokone.Piirra_taulukko();
			break;
		}

	} // Pelisilmukka

	system("PAUSE");
	return 0;
}

