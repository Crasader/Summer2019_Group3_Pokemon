#pragma once

#include "MyObject.h"
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class Route2NPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	Route2NPC();
	~Route2NPC();
	void Init() override;
	void Update(float deltaTime) override;
	vector<Pokemon*> GetListPokemon();
};