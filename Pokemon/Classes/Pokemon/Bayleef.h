#pragma once
#include "Pokemon.h"
#include "Chikorita.h"

class Bayleef : public Pokemon
{
public:
	Bayleef(Chikorita* it);
	~Bayleef();
	Pokemon* Evolve() override;
};