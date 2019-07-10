#pragma once
#include "Pokemon.h"
#include "Ralts.h"

class Kirlia : public Pokemon
{
public:
	Kirlia();
	Kirlia(Ralts* it);
	~Kirlia();
	Pokemon* Evolve() override;
};