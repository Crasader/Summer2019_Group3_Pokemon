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
private:
	static Bag* s_bag;
	vector<Pokemon*> m_pokemons, m_pokemons_over;
	vector<Item*> m_items;
};