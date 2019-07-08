#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class RouteNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	RouteNPC(Layer* layer);
	~RouteNPC();
	void Init() override;
	void Update(float deltaTime) override;
};

