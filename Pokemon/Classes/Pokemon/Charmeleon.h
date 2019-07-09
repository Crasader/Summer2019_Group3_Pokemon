#pragma once
#include "Pokemon.h"
#include "Charmander.h"

class Charmeleon : public Pokemon
{
public:
	Charmeleon();
	Charmeleon(Charmander* it);
	~Charmeleon();
	Pokemon* Evolve() override;
};