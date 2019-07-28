#pragma once
#include "Pokemon.h"

class Taillow : public Pokemon
{
public:
	Taillow();
	~Taillow();
	Pokemon* Evolve() override;
};