#pragma once
#include "Pokemon.h"

class Feebas : public Pokemon
{
public:
	Feebas();
	Feebas(int level);
	~Feebas();
	Pokemon* Evolve() override;
};