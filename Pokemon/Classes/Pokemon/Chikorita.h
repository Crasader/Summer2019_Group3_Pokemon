#pragma once
#include "Pokemon.h"

class Chikorita : public Pokemon
{
public:
	Chikorita();
	~Chikorita();
	Pokemon* Evolve() override;
};