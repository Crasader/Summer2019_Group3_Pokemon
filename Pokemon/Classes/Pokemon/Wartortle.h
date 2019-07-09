#pragma once
#include "Pokemon.h"
#include "Squirtle.h"

class Wartortle : public Pokemon
{
public:
	Wartortle();
	Wartortle(Squirtle* it);
	~Wartortle();
	Pokemon* Evolve() override;
};