#pragma once
#include "Pokemon.h"
#include "Electrike.h"

class Manectric : public Pokemon
{
public:
	Manectric();
	Manectric(int level);
	Manectric(Electrike* it);
	~Manectric();
};