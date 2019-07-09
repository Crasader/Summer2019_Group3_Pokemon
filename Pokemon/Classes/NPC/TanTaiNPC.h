#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class TanTaiNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	TanTaiNPC(Layer* layer);
	~TanTaiNPC();
	void Init() override;
	void Update(float deltaTime) override;
};


