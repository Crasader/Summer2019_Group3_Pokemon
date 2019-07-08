#pragma once
#include "Pokemon.h"

class Bayleef : public Pokemon
{
public:
	Bayleef();
	~Bayleef();
	void Init() override;
	void Update(float) override;
	void LevelUp() override;
};