#include "Item.h"

Item::Item()
{
}

Item::~Item()
{
}

void Item::Init(int id)
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(id);
}

int Item::GetGold()
{
	return this->gold;
}

string Item::GetName()
{
	return this->name;
}


void Item::SetGold(int gold)
{
	this->gold = gold;
}

void Item::SetName(string name)
{
	this->name = name;
}

int Item::GetNumber()
{
	return this->Number;
}

void Item::SetNumber(int index)
{
	this->Number = index;
}