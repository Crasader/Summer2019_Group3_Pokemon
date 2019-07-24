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
	return this->m_gold;
}

string Item::GetName()
{
	return this->m_name;
}


void Item::SetGold(int gold)
{
	this->m_gold = gold;
}

void Item::SetName(string name)
{
	this->m_name = name;
}


int Item::GetNumber()
{
	return this->m_number;
}

void Item::SetNumber(int index)
{
	this->m_number = index;
}

int Item::GetId()
{
	return this->m_id;
}

