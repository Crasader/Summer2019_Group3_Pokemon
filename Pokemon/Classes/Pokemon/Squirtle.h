#pragma once
#include "Pokemon.h"

class Squirtle : public Pokemon
{
public:
	Squirtle();
	~Squirtle();
	void Init() override;
	void Update(float deltaTime) override;
	void LevelUp() override;
	Pokemon* Evolve() override;
};