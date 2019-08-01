#pragma once
#include "Pokemon.h"
#include "Taillow.h"

class Swellow : public Pokemon
{
public:
	Swellow();
	Swellow(int level);
	Swellow(Taillow* it);
	~Swellow();
};