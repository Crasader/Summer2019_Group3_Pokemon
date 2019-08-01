#pragma once
#include "Pokemon.h"

class Charmander : public Pokemon
{
public:
	Charmander();
	Charmander(int level);
	~Charmander();
	Pokemon* Evolve() override;
};