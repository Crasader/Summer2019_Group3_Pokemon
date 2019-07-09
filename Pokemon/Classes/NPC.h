#pragma once
#include "MyObject.h"
#include <vector>
#include <Pokemon.h>
using namespace std;

class NPC : public MyObject
{
protected:
	string m_name;
	vector<Pokemon*> m_pokemons;
public:
	NPC();
	~NPC();
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	string GetName();
	void SetName(string name);
	void SetLevel(Pokemon *pokemon,int level);
	vector<Pokemon*> GetVector();
};
