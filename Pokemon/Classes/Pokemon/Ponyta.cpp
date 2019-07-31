#include "Ponyta.h"
#define hp 50
#define atk 50
#define def 55
#define speed 90

Ponyta::Ponyta()
{
}

Ponyta::Ponyta(int level) : Pokemon(level)
{
	this->Init(38, 39);
	//
	this->m_name = "Ponyta";
	this->m_type = MyObject::TYPE_FIRE;
	this->LearnSkill(new Ember());
	this->LearnSkill(new FirePunch());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Ponyta::~Ponyta()
{
}