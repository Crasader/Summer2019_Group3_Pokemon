#pragma once
#include "Pokemon.h"

class Charizard : public Pokemon
{
public:
	Charizard();
	~Charizard();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
};