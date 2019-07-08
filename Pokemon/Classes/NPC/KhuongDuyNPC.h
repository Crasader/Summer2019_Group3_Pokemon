#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class KhuongDuyNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	KhuongDuyNPC(Layer* layer);
	~KhuongDuyNPC();
	void Init() override;
	void Update(float deltaTime) override;
};

