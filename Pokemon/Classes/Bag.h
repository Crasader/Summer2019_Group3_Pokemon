#pragma once
#include "MyObject.h"
#include "cocos2d.h"
#include "Pokemon.h"
#include "Item.h"
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
	void SetGold(int gold);
	int GetGold();
	void AddItem(Item* item);
	void AddPokemonIntoMyList(int index);
	void RemovePokemonFormMyListIntoListOver(int index);
private:
	static Bag* s_bag;
	vector<Pokemon*> m_pokemons, m_pokemons_over;
	vector<Item*> m_items;
	int my_gold;
};