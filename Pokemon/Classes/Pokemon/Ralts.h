#pragma once
#include "Pokemon.h"

class Ralts : public Pokemon
{
public:
	Ralts();
	Ralts(int level);
	~Ralts();
	Pokemon* Evolve() override;
};