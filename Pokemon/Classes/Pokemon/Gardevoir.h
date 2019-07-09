#pragma once
#include "Pokemon.h"
#include "Kirlia.h"

class Gardevoir : public Pokemon
{
public:
	Gardevoir();
	Gardevoir(Kirlia* it);
	~Gardevoir();
};