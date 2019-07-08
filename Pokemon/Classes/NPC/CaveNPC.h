#pragma once
#include "MyObject.h"
#include <vector>
#include "NPC.h"

using namespace std;

class CaveNPC : public NPC
{
private:
	string name;
	vector<MyObject*> m_pokemons;
public:
	CaveNPC(Scene* scene);
	~CaveNPC();
	void Init() override;
	void Update(float deltaTime) override;
}; 
