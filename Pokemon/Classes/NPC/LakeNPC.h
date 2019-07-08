#pragma once
#include "MyObject.h"
#include <vector>
#include "NPC.h"

using namespace std;

class LakeNPC : public NPC
{
private:
	string name;
	vector<MyObject*> m_pokemons;
public:
	LakeNPC(Layer* layer);
	~LakeNPC();
	void Init() override;
	void Update(float deltaTime) override;
}; 
