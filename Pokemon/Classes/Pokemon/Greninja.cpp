#include "Greninja.h"
#define hp 54
#define atk 63
#define def 52
#define speed 97

Greninja::Greninja()
{
}

Greninja::Greninja(int level) : Pokemon(level)
{
	this->Init(24, 25);
	//
	this->m_name = "Greninja";
	this->m_type = MyObject::TYPE_WATER;
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Greninja::~Greninja()
{
}