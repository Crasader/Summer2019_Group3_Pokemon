#pragma once

#include "MyObject.h"
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class RoadNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	RoadNPC();
	~RoadNPC();
	void Update(float deltaTime) override;
};

