#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class ChampionNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	ChampionNPC(Layer* layer);
	~ChampionNPC();
	void Init() override;
	void Update(float deltaTime) override;
};


