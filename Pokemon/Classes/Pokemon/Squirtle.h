#pragma once
#include "Pokemon.h"

class Squirtle : public Pokemon
{
public:
	Squirtle();
	Squirtle(int level);
	~Squirtle();
	Pokemon* Evolve() override;
};