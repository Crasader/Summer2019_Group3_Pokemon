#pragma once
#include "MyObject.h"
#include <vector>
#include "NPC.h"

using namespace std;

class CityNPC : public NPC
{
private:
	string name;
	vector<MyObject*> m_pokemons;
public:
	CityNPC(Layer* scene);
	~CityNPC();
	void Init() override;
	void Update(float deltaTime) override;
};