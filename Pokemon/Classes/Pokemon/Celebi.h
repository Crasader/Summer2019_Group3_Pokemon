#pragma once
#include "Pokemon.h"

class Celebi : public Pokemon
{
public:
	Celebi();
	~Celebi();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
};