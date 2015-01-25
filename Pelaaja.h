#pragma once
class Pelaaja : public Kentta  // Pelaajaluokka peritty Kenttäluokasta.
{
public:
	void kysy_siirto(Kentta*);  // Kysyy siirron kordinaatit.

	Pelaaja();
	~Pelaaja();
};

