#pragma once
#include "Pokemon.h"

class Dragonair : public Pokemon
{
public:
	Dragonair();
	Dragonair(int level);
	~Dragonair();
	Pokemon* Evolve() override;
};