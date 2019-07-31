#pragma once
#include "Pokemon.h"
#include "Ralts.h"

class Kirlia : public Pokemon
{
public:
	Kirlia();
	Kirlia(int level);
	Kirlia(Ralts* it);
	~Kirlia();
	Pokemon* Evolve() override;
};