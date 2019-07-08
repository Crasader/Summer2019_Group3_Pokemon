#pragma once
#include "Pokemon.h"

class Beautifly : public Pokemon
{
public:
	Beautifly();
	~Beautifly();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
};