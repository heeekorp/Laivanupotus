#include "stdafx.h"
#include "Tietokone.h"


Tietokone::Tietokone()
{   // Tietokoneluokan oletusarvot.
	Laukaushistoria = 0;
	Nayta_laivat = false;
	Osuma1_x = 0;
	Osuma1_y = 0;
	Osuma2_x = 0;
	Osuma2_y = 0;
}

Tietokone::~Tietokone()
{
}

void Tietokone::Arvo_laivan_sijainti(Laiva *L){
	// Arvotaan laivan x,y ja suunta.

	// http://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
	random_device seeder;
	//then make a mersenne twister engine
	mt19937_64 engine(seeder());

	//then the easy part... the distribution
	uniform_int_distribution<int> dist(0, 9); // x ja y 0 - 9
	uniform_int_distribution<int> dist2(1, 4); // suunta 1 - 4

	//then just generate the integer like this:
	 L->Laiva_x = dist(engine);			// Arvotut koordinaatit ja suunta Laiva -olioon.
	 L->Laiva_y = dist(engine);
	 L->Laiva_suunta = dist2(engine);

}

void Tietokone::Tietokoneen_siirto(Kentta *PelaajanKentta){  // Pelaajan kett� referenssin�.
	// Generoi tietokoneen siirron.

	// Alustetaan tarvittavat muuttujat.
	int Ammu_x = 0, Ammu_y = 0, Toinen_laukaus_suunta = 0, Kolmas_laukaus_suunta = 0;
	bool Laukaus_ok = false;

	switch (Laukaushistoria)
	{
	case 0:{ // Ei aiempia osumia -> Ammu sattumanvaraisesti vapaisiin ruutuihin.
		while (true){
			// Arvotaan x ja y koordinaatit, kunnes saadaan koordinaatit johon ei ole viel� ammuttu.
			
			// http://stackoverflow.com/questions/12657962/how-do-i-generate-a-random-number-between-two-variables-that-i-have-stored
			random_device seeder;
			//then make a mersenne twister engine
			mt19937_64 engine(seeder());
			//then the easy part... the distribution
			uniform_int_distribution<int> dist(0, 9);
			//then just generate the integer like this:

			Ammu_x = dist(engine);
			Ammu_y = dist(engine);
			if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] < 2){ // Jos koordinaattiin ei ole viel� ammuttu...  0 = tyhj�  
																								//1 = laiva
				if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] == 1){ // Jos laukaus osuu...					
					Osuma1_x = Ammu_x;				   // Tallenntataan osuman koordinaatit
					Osuma1_y = Ammu_y;
					Laukaushistoria = 1;			   // ... ja tietokoneen laukaisuhistoria.
				}
				break; // Poistutaan arvonta silmukasta.
			}// if
		}//while
		break;
	}
	case 1:{ // Yksi aiempi osuma -> Ammu osuman yl�/ala/vas/oik puoleisiin ruutuihin, kunnes toinen osuma.
		while (true){
			// Arvotaan suunta johon ammutaan 1. osuman j�lkeen.
			random_device seeder;
			//then make a mersenne twister engine
			mt19937_64 engine(seeder());
			//then the easy part... the distribution
			uniform_int_distribution<int> dist(1, 4);
			//then just generate the integer like this:
 			Toinen_laukaus_suunta = dist(engine); // 1-4 -> 1=yl�s, 2-alas, 3-vasen, 4=oikea

			// Tarkasetetaan, ett� koordinaatti osuma 1:st� arvottuun suunntaan mahtuu kentt��n (0-9). 
			Laukaus_ok = false;
			if (Toinen_laukaus_suunta == 1 && (Osuma1_y - 1) >= 0) { Ammu_y = Osuma1_y - 1; Ammu_x = Osuma1_x; Laukaus_ok = true; }
			if (Toinen_laukaus_suunta == 2 && (Osuma1_y + 1) <= 9) { Ammu_y = Osuma1_y + 1; Ammu_x = Osuma1_x; Laukaus_ok = true; }
			if (Toinen_laukaus_suunta == 3 && (Osuma1_x - 1) >= 0) { Ammu_x = Osuma1_x - 1; Ammu_y = Osuma1_y; Laukaus_ok = true; }
			if (Toinen_laukaus_suunta == 4 && (Osuma1_x + 1) <= 9) { Ammu_x = Osuma1_x + 1; Ammu_y = Osuma1_y; Laukaus_ok = true; }
			
			// Jos laukauksen koordinaatti mahtuu kentt��n ja siihen ei ole viel� ammuttu.
			if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] < 2 && Laukaus_ok == true){
				// Jos koordinaateissa on laiva...
				if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] == 1){
					// P�ivitetaan tietokoneen laukaisuhistoria ja tallentaan Osuma2
					Laukaushistoria = 2;
					Osuma2_x = Ammu_x;
					Osuma2_y = Ammu_y;
				}
			
				break; // Poistutaan arvota silmukasta.
			}
		}// while
		break;
	}
	case 2:{	// Laivaan kaksi osumaa- > Jos osumat per�kk�in, ammu osumien oik/vas -puolelle
				//						   Jos osumat allekkain, ammu osumien yl�/ala -puolelle
		// Miten osumat sijoittuvat ruudukkoon
		if (Osuma1_y != Osuma2_y){ Kolmas_laukaus_suunta = 1; } // Osumat allekkain 	
		if (Osuma1_x != Osuma2_x){ Kolmas_laukaus_suunta = 2; } // Osumat per�kk�in
		int dummy = 0;
		// Jos osuma 1 on osuma 2:n yl�puolella, vaihdetaan koordinaatit toisinp�n.
		if (Osuma2_y > Osuma1_y){
			dummy = Osuma1_y;
			Osuma1_y = Osuma2_y;
			Osuma2_y = dummy;
		}
		// Jos osuma 1 on osuma 2:n vasemmalla puolella, vaihdetaan koordinaatit toisinp�n.
		if (Osuma2_x > Osuma1_x){
			dummy = Osuma1_x;
			Osuma1_x = Osuma2_x;
			Osuma2_x = dummy;
		}
		
		// Seuraava laukaus.
	
		// Osuma 1 ja 2 p��llekk�in....
		if (Kolmas_laukaus_suunta == 1){

			// Ammutaan Osuma2:n yl�puolelle (jos ruutuun ei ole viel� ammuttu ja ruutu ei ole ruudukon ulkopuolella)
			if (PelaajanKentta->Ruudukko[Osuma2_x][Osuma2_y - 1] < 2 && (Osuma2_y - 1) >= 0){
				Ammu_x = Osuma2_x;
				Ammu_y = Osuma2_y - 1;
				// Jos laukaus osuu paivitetaan Osuma2:n y-koordinaattia. 
				if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] == 1){ Osuma2_y--; }

				break; // switch casesta
			}

			// Jos osuma 2:n yl�puolinen ruutu ei ole vapaa/ei mahdu ruudukkoon, ammutaan osuma 1:n alapuolelle, jos se on vapaa
			if (PelaajanKentta->Ruudukko[Osuma1_x][Osuma1_y + 1] < 2 && (Osuma1_y + 1) <= 9){
				Ammu_x = Osuma1_x;
				Ammu_y = Osuma1_y + 1;
				// Jos laukaus osuu p�ivitet��n Osuma1:n y-koordinaattia.
				if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] == 1){ Osuma1_y++; }
					
				break; // switch casesta
			}
		}

		// Osuma 1 ja Osuma 2 p��llekk�in.
		if (Kolmas_laukaus_suunta == 2){
				
			// Ammutaan Osuma2:n vasemmalle puolelle, jos ruutu vapaa, ja ruutu ei ruudukon ulkopuolella...
			if (PelaajanKentta->Ruudukko[Osuma2_x - 1][Osuma2_y] < 2 && (Osuma2_x - 1) >= 0){
				Ammu_y = Osuma2_y;
				Ammu_x = Osuma2_x - 1;
				// Jos laukaus osuu p�ivitet��n Osuma2:n x-koordinaattia.
				if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] == 1){ Osuma2_x--; }
					
				break; // switch casesta
			}

			// Jos osuma 2:n vasemmanpuoleinen ruutu ei ole vapaa/ei mahdu ruudukkoon, ammutaan osuma 1:n oikealle puolelle, jos se on vapaa
			if (PelaajanKentta->Ruudukko[Osuma1_x + 1][Osuma1_y] < 2 && (Osuma1_x + 1) <= 9){
				Ammu_y = Osuma1_y;
				Ammu_x = Osuma1_x + 1;
				// Jos laukaus osuu p�ivitet��n Osuma1:n x-koordinaattia.
				if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] == 1){ Osuma1_x++; }
					
				break; // switch casesta
			}
		}

		// Jos 2 osumaa, ja osumien molemmissa p�iss� ohilaukaus tai kent�nreuna, palataan case 1:een
		Laukaushistoria = 1;
		Tietokoneen_siirto(PelaajanKentta);
			
		
			
		break;
	}
	default:
		break;
	}

	// P�ivitet��n tietokoneen laukaus pelaajan ruudukkoon.
	if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] == 0){ // Laukaus ohi 
		PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] = 2;
		cout << "Tietokoneen laukaus ohi!" << endl;
	}
	if (PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] == 1){ // Osuma
		PelaajanKentta->Ruudukko[Ammu_x][Ammu_y] = 3;
		cout << "Tietokoneen laukaus osui!" << endl;
	}

}