#pragma once
#include "Pokemon.h"
#include "Pidgey.h"

class Pidgeotto : public Pokemon
{
public:
	Pidgeotto();
	Pidgeotto(int level);
	Pidgeotto(Pidgey* it);
	~Pidgeotto();
	Pokemon* Evolve() override;
};