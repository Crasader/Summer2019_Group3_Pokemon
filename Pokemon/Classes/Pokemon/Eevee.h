#pragma once
#include "Pokemon.h"

class Eevee : public Pokemon
{
public:
	Eevee();
	~Eevee();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
};