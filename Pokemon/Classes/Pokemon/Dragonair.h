#pragma once
#include "Pokemon.h"

class Dragonair : public Pokemon
{
public:
	Dragonair();
	~Dragonair();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
};