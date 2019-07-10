#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class CityNPC : public NPC
{
private:
	string name;
public:
	CityNPC(Layer* layer);
	~CityNPC();
	void Init() override;
	void Update(float deltaTime) override;
};
#pragma once
