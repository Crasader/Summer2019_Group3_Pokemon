#pragma once
#include "Pokemon.h"

class Feebas : public Pokemon
{
public:
	Feebas();
	~Feebas();
	Pokemon* Evolve() override;
};