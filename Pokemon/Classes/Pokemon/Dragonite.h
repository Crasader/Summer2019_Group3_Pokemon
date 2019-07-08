#pragma once
#include "Pokemon.h"

class Dragonite : public Pokemon
{
public:
	Dragonite();
	~Dragonite();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
};