#pragma once
#include "MyObject.h"
#include "cocos2d.h"
#include "Pokemon.h"
#include "Item.h"
#include "include_pokemon.h"
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

class Bag :public MyObject
{
public:
	static Bag* GetInstance();
	Bag();
	~Bag();
	void Init() override;
	void Update(float deltaTime) override;
	vector<Pokemon*> GetListPokemon();
	vector<Pokemon*> GetListPokemonOver();
	vector<Item*> GetListItem();
	void AddPokemon(Pokemon* pokemon);
	int GetCountPokemon();
	void ChangePokemon(int index);
	void SetGold(int gold);
	int GetGold();
	void AddItem(Item* item);
	void AddPokemonIntoMyList(Pokemon *pokemon,int index);
	void ReleasePokemonOver(int index);
	void ReleasePokemon(int index);
	void RemovePokemonFormMyListToListOver(Pokemon *pokemon, int index);
	void SortList();
	void CreateListItem();
	int SizeOfListPokemon();
	int SizeOfListPokemonOver();
	void HealthPokemon(int index, Pokemon* pokemon);
private:
	static Bag* m_instance;
	vector<Pokemon*> m_pokemons = { nullptr, nullptr ,nullptr, nullptr, nullptr ,nullptr };
	vector<Pokemon*> m_pokemons_over = { nullptr, nullptr, nullptr ,nullptr, nullptr, nullptr ,nullptr, nullptr, nullptr ,nullptr};
	vector<Item*> m_items;
	int my_gold;
};