#pragma once
#include "Pokemon.h"

class Electrike : public Pokemon
{
public:
	Electrike();
	~Electrike();
	Pokemon* Evolve() override;
};