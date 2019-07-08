#pragma once
#include "Pokemon.h"

class Chikorita : public Pokemon
{
public:
	Chikorita();
	~Chikorita();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
};