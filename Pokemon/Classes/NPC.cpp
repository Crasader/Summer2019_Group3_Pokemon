#include "NPC.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::Init()
{
}

void NPC::Update(float deltaTime)
{
}

string NPC::GetName()
{
	return this->m_name;
}

void NPC::SetName(string name)
{
	this->m_name = name;
}

void NPC::SetLevel(Pokemon * pokemon, int level)
{
	int levelup = level - pokemon->GetLevel();
	for (int i = 1; i < levelup; i++);
	{
		pokemon->LevelUp();
	}
}

vector<Pokemon*> NPC::GetVector()
{
	return this->m_pokemons;
}
