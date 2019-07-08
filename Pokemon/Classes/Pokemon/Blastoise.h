#pragma once
#include "Pokemon.h"
#include "Wartortle.h"

class Blastoise : public Pokemon
{
public:
	Blastoise();
	Blastoise(Wartortle* it);
	~Blastoise();
};