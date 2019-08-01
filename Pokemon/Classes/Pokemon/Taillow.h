#pragma once
#include "Pokemon.h"

class Taillow : public Pokemon
{
public:
	Taillow();
	Taillow(int level);
	~Taillow();
	Pokemon* Evolve() override;
};