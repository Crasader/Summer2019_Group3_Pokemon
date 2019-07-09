#pragma once
#include "MyObject.h"
#include <vector>
using namespace std;

class NPC : public MyObject
{
protected:
	string m_name;
	vector<MyObject> m_pokemons;
public:
	NPC();
	~NPC();
	virtual void Init() override;
	virtual void Update(float deltaTime) override;
	string GetName();
	void SetName(string name);
};