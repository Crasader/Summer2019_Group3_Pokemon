#pragma once
#include "Pokemon.h"

class Electrike : public Pokemon
{
public:
	Electrike();
	Electrike(int level);
	~Electrike();
	Pokemon* Evolve() override;
};