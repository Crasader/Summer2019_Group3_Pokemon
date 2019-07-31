#include "Bag.h"
#include "Trainer.h"

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
	if (this->GetCountPokemon() < 6)
	{
		for (int i = 0; i < 6; i++)
		{
			if (this->m_pokemons.at(i) == nullptr)
			{
				this->m_pokemons.at(i) = pokemon;
				break;
			}
		}
	}
	else
	{
		this->m_pokemons_over.at(this->SizeOfListPokemonOver()) = pokemon;
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

void Bag::AddPokemonIntoMyList(Pokemon *pokemon,int index)
{
	for (int i = 0; i < 6; i++)
	{
		if (this->m_pokemons.at(i) == nullptr)
		{
			this->m_pokemons.at(i) = pokemon;
			break;
		}
	}
	this->m_pokemons_over.at(index) = nullptr;
	this->SortList();
}

void Bag::ReleasePokemonOver(int index)
{
	this->m_pokemons_over.at(index) = nullptr;
	this->SortList();
}

void Bag::ReleasePokemon(int index)
{
	this->m_pokemons.at(index) = nullptr;
	this->SortList();
}

void Bag::RemovePokemonFormMyListToListOver(Pokemon *pokemon,int index)
{
	for (int i = 0; i < 10; i++)
	{
		if (this->m_pokemons_over.at(i) == nullptr)
		{
			this->m_pokemons_over.at(i) = pokemon;
			break;
		}
	}
	this->m_pokemons.at(index) = nullptr;
	this->SortList();
}

void Bag::SortList()
{
	for (int i=0; i < this->m_pokemons.size()-1; i++)
	{
		if (this->m_pokemons.at(i) == nullptr)
		{
			this->m_pokemons.at(i) = this->m_pokemons.at(i + 1);
			this->m_pokemons.at(i + 1) = nullptr;
		}
	}
	for (int j = 0; j < this->m_pokemons_over.size() - 1; j++)
	{
		if (this->m_pokemons_over.at(j) == nullptr)
		{
			this->m_pokemons_over.at(j) = this->m_pokemons_over.at(j + 1);
			this->m_pokemons_over.at(j + 1) = nullptr;
		}
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

int Bag::SizeOfListPokemon()
{
	int cout=0;
	for (int i = 0; i < this->m_pokemons.size(); i++)
	{
		if (this->m_pokemons.at(i) != nullptr)
		{
			cout++;
		}
	}
	return cout;
}
int Bag::SizeOfListPokemonOver()
{
	int cout = 0;
	for (int i = 0; i < this->m_pokemons_over.size(); i++)
	{
		if (this->m_pokemons_over.at(i) != nullptr)
		{
			cout++;
		}
	}
	return cout;
}

void Bag::HealthPokemon(int index, Pokemon * pokemon)
{
	if (index == 0)
	{
		int min = std::min(pokemon->GetCurrentHP() + 50, pokemon->GetMaxHP());
		pokemon->SetCurrentHP(min);
	}
	if (index == 1)
	{
		int min = std::min(pokemon->GetCurrentHP() + 100, pokemon->GetMaxHP());
		pokemon->SetCurrentHP(min);
	}
	if (index == 2||index==5)
	{
		pokemon->SetCurrentHP(pokemon->GetMaxHP());
	}
	if (index == 4)
	{
		pokemon->SetCurrentHP(pokemon->GetMaxHP() / 2);
	}
}