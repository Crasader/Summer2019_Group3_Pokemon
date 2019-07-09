#pragma once
#include "Pokemon.h"
#include <vector>
#include "NPC.h"

using namespace std;

class MinhVuongNPC : public NPC
{
private:
	string name;
	vector<Pokemon*> m_pokemons;
public:
	MinhVuongNPC(Layer* layer);
	~MinhVuongNPC();
	void Init() override;
	void Update(float deltaTime) override;
};