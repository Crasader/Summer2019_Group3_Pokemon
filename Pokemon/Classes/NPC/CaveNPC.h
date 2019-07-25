#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class CaveNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	CaveNPC();
	~CaveNPC();
	void Init() override;
	void Update(float deltaTime) override;
};
#pragma once
