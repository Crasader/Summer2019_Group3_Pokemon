#pragma once
#include "Pokemon.h"
#include "Pidgeotto.h"

class Pidgeot : public Pokemon
{
public:
	Pidgeot();
	Pidgeot(Pidgeotto* it);
	~Pidgeot();
};