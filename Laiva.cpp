#include "stdafx.h"
#include "Laiva.h"


Laiva::Laiva()
{	// Laivan oletusarvot.
	Laiva_x = 0;
	Laiva_y = 0;
	Laiva_suunta = 0;
	Laiva_koko = 0;
}

Laiva::~Laiva()
{
}

void Laiva::Lisaa_laiva(){
	//Kysyy listättävän laivan koordinaatit ja suunnan.

	char x[1] = "";
	cout << "Lisää " << Laiva_koko << ":n ruudun kokoinen laiva kenttään." << endl;
	cout << "Anna laivan alkukoordinaatti X (A-J):";
	cin >> x[0];
	if (x[0] == 'A' || x[0] == 'a'){ Laiva_x = 0; }
	if (x[0] == 'B' || x[0] == 'b'){ Laiva_x = 1; }
	if (x[0] == 'C' || x[0] == 'c'){ Laiva_x = 2; }
	if (x[0] == 'D' || x[0] == 'd'){ Laiva_x = 3; }
	if (x[0] == 'E' || x[0] == 'e'){ Laiva_x = 4; }
	if (x[0] == 'F' || x[0] == 'f'){ Laiva_x = 5; }
	if (x[0] == 'G' || x[0] == 'g'){ Laiva_x = 6; }
	if (x[0] == 'H' || x[0] == 'h'){ Laiva_x = 7; }
	if (x[0] == 'I' || x[0] == 'i'){ Laiva_x = 8; }
	if (x[0] == 'J' || x[0] == 'j'){ Laiva_x = 9; }

	cout << "Anna laivan alkukoordinaatti Y (1-9):";
	cin >> Laiva_y;
	Laiva_y--;

	// Jos laivan koko on 1, asetetaan suunnaksi automaattisesti 1
	if (Laiva_koko != 1){
		cout << "Anna laivan suunta(1=ylös, 2=alas, 3=vasen, 4=okea):";
		cin >> Laiva_suunta;
	}
	else{ Laiva_suunta = 1; }
}

