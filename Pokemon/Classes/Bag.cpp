#include "Bag.h"
#include "Trainer.h"
#include "Item\Potion.h"
#include "Item\MaxPotion.h"
#include "Item\SuperPotion.h"
#include "Item\Revive.h"
#include "Item\MaxRevive.h"
#include "Item\Ether.h"
#include "Item\LeafStone.h"
#include "Item\FireStone.h"
#include "Item\ThunderStone.h"
#include "Item\WaterStone.h"

Bag::Bag()
{
	this->Init();
	this->my_gold = 100;
	this->CreateListItem();
}

Bag::~Bag()
{
}

Bag * Bag::m_instance = nullptr;

Bag * Bag::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = new Bag();
	}
	return m_instance;
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

int Bag::GetCountPokemon()
{
	int count = 0;
	for (int i = 0; i < 6; i++)
	{
		auto pokemon = this->m_pokemons.at(i);
		if (pokemon != nullptr)
		{
			if (pokemon->IsAlive() == true)
			{
				count++;
			}
		}
	}
	return count;
}

void Bag::ChangePokemon(int index)
{
	Pokemon* temp = this->m_pokemons.at(0);
	this->m_pokemons.at(0) = this->m_pokemons.at(index);
	this->m_pokemons.at(index) = temp;
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

void Bag::CreateListItem()
{
	Potion *potion = new Potion();
	this->m_items.push_back(potion);
	SuperPotion *superPotion = new SuperPotion();
	this->m_items.push_back(superPotion);
	MaxPotion *maxPotion = new MaxPotion();
	this->m_items.push_back(maxPotion);
	Ether *ether = new Ether();
	this->m_items.push_back(ether);
	Revive *revive = new Revive();
	this->m_items.push_back(revive);
	MaxRevive *maxRevive = new MaxRevive();
	this->m_items.push_back(maxRevive);
	FireStone *fireStone = new FireStone();
	this->m_items.push_back(fireStone);
	LeafStone *leafStone = new LeafStone();
	this->m_items.push_back(leafStone);
	ThunderStone *thunderStone = new ThunderStone();
	this->m_items.push_back(thunderStone);
	WaterStone *waterStone = new WaterStone();
	this->m_items.push_back(waterStone);
}