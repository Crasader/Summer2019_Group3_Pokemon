#pragma once
#include "Pokemon.h"
#include "Pidgey.h"

class Pidgeotto : public Pokemon
{
public:
	Pidgeotto();
	Pidgeotto(Pidgey* it);
	~Pidgeotto();
	Pokemon* Evolve() override;
};