#pragma once
class Laiva
{
public:
	int Laiva_x;	// Laivan x-koordinaatti
	int Laiva_y;	// Laivan y-koordinaatti
	int Laiva_suunta; // Mihin suuntaan alkukoordinaateista laiva sijoittuu.
	int Laiva_koko;	// Laivan pituus

	void Lisaa_laiva();	// Kysyy laivan koordinaatit ja suunnan.
	Laiva();
	~Laiva();
};

