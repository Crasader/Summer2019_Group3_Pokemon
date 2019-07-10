#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class TanNgocNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	TanNgocNPC(Layer* layer);
	~TanNgocNPC();
	void Init() override;
	void Update(float deltaTime) override;
};

