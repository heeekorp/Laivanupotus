#pragma once
class Pelaaja : public Kentta  // Pelaajaluokka peritty Kentt�luokasta.
{
public:
	void kysy_siirto(Kentta*);  // Kysyy siirron kordinaatit.

	Pelaaja();
	~Pelaaja();
};

