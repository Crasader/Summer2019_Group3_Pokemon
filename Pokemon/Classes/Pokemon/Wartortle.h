#pragma once
#include "Pokemon.h"
#include "Squirtle.h"

class Wartortle : public Pokemon
{
public:
	Wartortle();
	Wartortle(Squirtle* it);
	~Wartortle();
	void Init() override;
	void Update(float deltaTime) override;
	void LevelUp() override;
	Pokemon* Evolve() override;
};