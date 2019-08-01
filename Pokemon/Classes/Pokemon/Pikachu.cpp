#include "Pikachu.h"
#define hp 40
#define atk 55
#define def 40
#define speed 90

Pikachu::Pikachu()
{
}

Pikachu::Pikachu(int level) : Pokemon(level)
{
	this->Init(36, 37);
	//
	this->m_name = "Pikachu";
	this->m_type = MyObject::TYPE_ELECTRIC;
	this->m_listSkill = { new QuickAttack(), new Spark(), new Thunderbolt() };
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Pikachu::~Pikachu()
{
}