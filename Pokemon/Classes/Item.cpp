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

int Item::GetType()
{
	return this->type;
}

void Item::SetGold(int gold)
{
	this->gold = gold;
}

void Item::SetName(string name)
{
	this->name = name;
}

void Item::SetType(int type)
{
	this->type = type;
}
