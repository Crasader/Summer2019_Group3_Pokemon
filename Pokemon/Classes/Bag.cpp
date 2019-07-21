#include "Bag.h"
#include "Trainer.h"

Bag::Bag()
{
	this->Init();
	this->my_gold = 100;
}
Bag::~Bag()
{
}

Bag * Bag::s_bag = nullptr;

Bag * Bag::GetInstance()
{
	if (s_bag == nullptr)
	{
		s_bag = new Bag();
	}
	return s_bag;
}
void Bag::Init()
{
}

void Bag::Update(float deltaTime)
{
}

vector<Pokemon*> Bag::GetListPokemon()
{
	return this->m_pokemons;
}

vector<Pokemon*> Bag::GetListPokemonOver()
{
	return this->m_pokemons_over;
}

vector<Item*> Bag::GetListItem()
{
	return this->m_items;
}


void Bag::AddPokemon(Pokemon* pokemon)
{
	if (this->m_pokemons.size() < 6)
	{
		this->m_pokemons.push_back(pokemon);
	}
	else
	{
		this->m_pokemons_over.push_back(pokemon);
	}
}

void Bag::SetGold(int gold)
{
	this->my_gold = gold;
}

int Bag::GetGold()
{
	return this->my_gold;
}

void Bag::AddItem(Item * item)
{
	this->m_items.push_back(item);
}

