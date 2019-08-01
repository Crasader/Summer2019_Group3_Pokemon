#include "Shaymin.h"
#define hp 40
#define atk 52
#define def 43
#define speed 65

Shaymin::Shaymin()
{
}

Shaymin::Shaymin(int level) : Pokemon(level)
{
	this->Init(82, 83);
	//
	this->m_name = "Shaymin";
	this->m_type = MyObject::TYPE_GRASS;
	this->LearnSkill(new LeechSeed());
	this->LearnSkill(new EnergyBall());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Shaymin::~Shaymin()
{
}