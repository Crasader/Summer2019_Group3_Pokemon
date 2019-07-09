#pragma once
#include "Pokemon.h"

class Squirtle : public Pokemon
{
public:
	Squirtle();
	~Squirtle();
	Pokemon* Evolve() override;
};