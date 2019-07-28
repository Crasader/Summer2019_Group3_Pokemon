#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class LakeNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	LakeNPC();
	~LakeNPC();
	void Init() override;
	void Update(float deltaTime) override;
}; 
