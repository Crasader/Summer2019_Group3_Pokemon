#pragma once
#include "Pokemon.h"

class Charmander : public Pokemon
{
public:
	Charmander();
	~Charmander();
	Pokemon* Evolve() override;
};

