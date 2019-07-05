#pragma once
#include "Pokemon.h"

class Charmander : public Pokemon
{
public:
	Charmander();
	~Charmander();
	void Init() override;
	void Update(float deltaTime) override;
};

