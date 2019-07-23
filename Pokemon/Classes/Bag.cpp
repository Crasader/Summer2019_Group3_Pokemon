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
	for (int i = 0; i < 9; i++)
	{

		m_items.push_back();
	}
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

void Bag::AddPokemonIntoMyList(int index)
{
	if (this->m_pokemons.size() > 6)
	{
		CCLOG("My list pokemon full 6 slot");
	}
	else
	{
		this->m_pokemons.push_back(this->m_pokemons_over.at(index));
		//this->m_pokemons_over.erase.at(index);
	}
}

void Bag::RemovePokemonFormMyListIntoListOver(int index)
{
	if (this->m_pokemons.size() > 10)
	{
		CCLOG("List pokemon over full 10 slot");
	}
	else
	{
		this->m_pokemons_over.push_back(this->m_pokemons.at(index));
		//this->m_pokemons.erase.at(index);
	}
}

