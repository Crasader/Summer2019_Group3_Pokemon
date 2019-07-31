#pragma once
#include "Pokemon.h"
#include <vector>
using namespace std;

class NPC : public MyObject
{
protected:
	string m_name;
	vector<Pokemon*> m_pokemons;
	bool m_state;
public:
	NPC();
	~NPC();
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	string GetName();
	void SetName(string name);
};