#include "stdafx.h"
#include "Kentta.h"


Kentta::Kentta()
{   // Nollataan ruudukko
	memset(Ruudukko, 0, sizeof(Ruudukko[0][0]) * 10 * 10); // 10x10 ruudukon ruutujen arvoksi 0
}

Kentta::~Kentta()
{
}

void Kentta::Piirra_taulukko(){
	// Piirtää pelikentän.

	cout << "   A B C D E F G H I J" << endl;
	cout << "----------------------" << endl;
	for (int iteratorY = 0; iteratorY < 10; iteratorY++){
		cout << iteratorY + 1;
		if (iteratorY < 9){ cout << " "; }

		for (int iteratorX = 0; iteratorX < 10; iteratorX++){
			if (Ruudukko[iteratorX][iteratorY] == 0){ cout << " -"; } // tyhjä
			if (Ruudukko[iteratorX][iteratorY] == 1 && Nayta_laivat == false){ cout << " -"; } // Tietokone, laivat piiloon.
			if (Ruudukko[iteratorX][iteratorY] == 1 && Nayta_laivat == true){ cout << " +"; } // Pelaaja, laivat näkyviin.
			if (Ruudukko[iteratorX][iteratorY] == 2){ cout << " /"; } // ohi
			if (Ruudukko[iteratorX][iteratorY] == 3){ cout << " X"; } // osuma
			if (Ruudukko[iteratorX][iteratorY] == 4){ cout << " O"; } // uponnut
		}
		cout << endl;
	}
}

bool Kentta::Tarkista_laivan_koordinaatit(Laiva L){
	// Tarkistaa onko laivan koorinaatit ja suunta kelvolliset.

	// Käydän läpi jokainen ruutu, jossa laiva sijaitsee.
	for (int iterator = 0; iterator < L.Laiva_koko; iterator++){
		
		// Mahtuuko laiva kentälle
		if (L.Laiva_x < 0 || L.Laiva_x > 9 || L.Laiva_y < 0 || L.Laiva_y > 9){ return false; } // palauttaa false
		
		// Onko laivan koordinaatti vapaa
		if (Ruudukko[L.Laiva_x][L.Laiva_y] != 0) { return false; } // palautta false
		
		// Seuraava koordinaatti
		if (L.Laiva_suunta == 1){ L.Laiva_y--; } // suunta ylös
		if (L.Laiva_suunta == 2){ L.Laiva_y++; } // suunta alas
		if (L.Laiva_suunta == 3){ L.Laiva_x--; } // suunta vasemalle
		if (L.Laiva_suunta == 4){ L.Laiva_x++; } // suunta oikealle
	}
	return true;  // Jos kaikki ruudut, jossa laiva sijaitsee, ovat kelvollisia.

void Kentta::Aseta_laiva_kenttaan(Laiva L){
	// Asettaa laivan ruudukkoon koordinaattien, suunnan ja koon mukaan.

	// Asetetaan laiva jokaiseen ruutuun koon mukaaan.
	for (int iterator = 0; iterator < L.Laiva_koko; iterator++){
		
		// Asetetaan laivan koordinaattien mukainen paikka ruudukosta laivaksi (= 1)
		Ruudukko[L.Laiva_x][L.Laiva_y] = 1;
		
		// Päivitetään koordinaatteja suunnan mukaan.
		if (L.Laiva_suunta == 1){ L.Laiva_y--; }
		if (L.Laiva_suunta == 2){ L.Laiva_y++; }
		if (L.Laiva_suunta == 3){ L.Laiva_x--; }
		if (L.Laiva_suunta == 4){ L.Laiva_x++; }
	}

}

bool Kentta::tarkista_laivat(vector<Laiva>*Laivat){
	// Tarkisetaan onko jokin laivoista uponnut.

	// Alusetetaan muuttujat
	bool laiva_ok = false;
	int Suunta_x = 0, Suunta_y = 0;

	// Käydään läpi laivat vektori
	for (unsigned int iteratorA = 0; iteratorA < (*Laivat).size(); iteratorA++){
		
		Suunta_x = 0;
		Suunta_y = 0;

		// Käydään läpi laivan koordinaatit
		for (int iteratorB = 0; iteratorB < (*Laivat).at(iteratorA).Laiva_koko; iteratorB++){
			
			laiva_ok = false;
			
			// Käydään läpi laivan elementit alkukoordinaateista laivan koon verran laivan suunnan suuntaan. 
			if ((*Laivat).at(iteratorA).Laiva_suunta == 1){ Suunta_y = -iteratorB; } //laivan suunta(1=ylös, 2=alas, 3=vasen, 4=okea)
			if ((*Laivat).at(iteratorA).Laiva_suunta == 2){ Suunta_y = iteratorB; }
			if ((*Laivat).at(iteratorA).Laiva_suunta == 3){ Suunta_x = -iteratorB; }
			if ((*Laivat).at(iteratorA).Laiva_suunta == 4){ Suunta_x = iteratorB; }
		
			// Jos laivan jonkin elementin tila jokin muu kuin 3, = uponnut.
			if (Ruudukko[(*Laivat).at(iteratorA).Laiva_x + Suunta_x][(*Laivat).at(iteratorA).Laiva_y + Suunta_y] != 3){
				laiva_ok = true;
				break; // Poistutaan silmukasta.
			} 
		} // for

		// Jos laivan kaikkien elemettien tila on 3, = osuma, poistetaan laiva Laivatvektorista,
		// ja asetetetaan laiva uponneeksi ruudukossa (uponnut = 4) .
		if (laiva_ok == false){
			
			Suunta_x = 0;
			Suunta_y = 0;
			for (int iteratorC = 0; iteratorC < (*Laivat).at(iteratorA).Laiva_koko; iteratorC++){
				if ((*Laivat).at(iteratorA).Laiva_suunta == 1){ Suunta_y = -iteratorC; } //laivan suunta(1=ylös, 2=alas, 3=vasen, 4=okea)
				if ((*Laivat).at(iteratorA).Laiva_suunta == 2){ Suunta_y = iteratorC; }
				if ((*Laivat).at(iteratorA).Laiva_suunta == 3){ Suunta_x = -iteratorC; }
				if ((*Laivat).at(iteratorA).Laiva_suunta == 4){ Suunta_x = iteratorC; }
				Ruudukko[(*Laivat).at(iteratorA).Laiva_x + Suunta_x][(*Laivat).at(iteratorA).Laiva_y + Suunta_y] = 4;
			}

			(*Laivat).erase((*Laivat).begin() + iteratorA);
			
			break; // Poistutaan silmukasta.
		}
	}// for

	return laiva_ok;  // false, jos jokin laivoista uponnut.
}
