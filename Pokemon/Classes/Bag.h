#pragma once
#include "MyObject.h"
#include "cocos2d.h"
#include "Pokemon.h"
#include "Item.h"
#include "include_pokemon.h"

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
	void ChangePokemon(int index);
	void SetGold(int gold);
	int GetGold();
	void AddItem(Item* item);
	void AddPokemonIntoMyList(int index);
	void RemovePokemonFormMyListIntoListOver(int index);
	void CreateListItem();
private:
	static Bag* m_instance;
	vector<Pokemon*> m_pokemons = { new Charmander(), new Squirtle(), new Chikorita(), nullptr, nullptr, nullptr };
	vector<Pokemon*> m_pokemons_over;
	vector<Item*> m_items;
	int my_gold;
};