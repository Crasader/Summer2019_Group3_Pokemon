#pragma once
#include "Pokemon.h"

class Pidgey : public Pokemon
{
public:
	Pidgey();
	Pidgey(int level);
	~Pidgey();
	Pokemon* Evolve() override;
};