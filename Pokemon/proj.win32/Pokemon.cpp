#include "Pokemon.h"



Pokemon::Pokemon()
{
}


Pokemon::~Pokemon()
{
}

void Pokemon::Init()
{
}

void Pokemon::Update(float deltaTime)
{
}

string Pokemon::GetName()
{
	return this->m_name;
}

void Pokemon::SetName(string name)
{
	this->m_name = name;
}

int Pokemon::GetType()
{
	return this->m_type;
}

void Pokemon::SetType(int type)
{
	this->m_type = type;
}

int Pokemon::GetHP()
{
	return this->m_health;
}

void Pokemon::SetHP(int health)
{
	this->m_health = health;
}

int Pokemon::GetLevel()
{
	return this->m_level;
}

void Pokemon::SetLevel(int level)
{
	this->m_level = level;
}

int Pokemon::GetAtk()
{
	return this->m_attack;
}

void Pokemon::SetAtk(int atk)
{
	this->m_attack = atk;
}

int Pokemon::GetDef()
{
	return this->m_defense;
}

void Pokemon::SetDef(int def)
{
	this->m_defense = def;
}

int Pokemon::GetAtkSpeed()
{
	return this->m_attackSpeed;
}

void Pokemon::SetAtkSpeed(int atkSpeed)
{
	this->m_attackSpeed = atkSpeed;
}

int Pokemon::GetCurrentExp()
{
	return this->m_currentExp;
}

void Pokemon::SetCurrentExp(int exp)
{
	this->m_currentExp = exp;
}

int Pokemon::GetMaxExp()
{
	return this->m_maxExp;
}

void Pokemon::SetMaxExp(int exp)
{
	this->m_maxExp = exp;
}
