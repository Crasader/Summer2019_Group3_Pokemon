#pragma once
#include "Pokemon.h"
#include "Dragonair.h"

class Dragonite : public Pokemon
{
public:
	Dragonite();
	Dragonite(Dragonair* it);
	~Dragonite();
};