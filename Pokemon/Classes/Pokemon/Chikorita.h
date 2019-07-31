#pragma once
#include "Pokemon.h"

class Chikorita : public Pokemon
{
public:
	Chikorita();
	Chikorita(int level);
	~Chikorita();
	Pokemon* Evolve() override;
};