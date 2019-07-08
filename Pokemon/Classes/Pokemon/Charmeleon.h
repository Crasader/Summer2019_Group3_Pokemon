#pragma once
#include "Pokemon.h"

class Charmeleon : public Pokemon
{
public:
	Charmeleon();
	~Charmeleon();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
	Pokemon* Evolve() override;
};