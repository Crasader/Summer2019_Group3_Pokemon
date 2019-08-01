#include "Beautifly.h"
#define hp 45
#define atk 45
#define def 35
#define speed 60

Beautifly::Beautifly()
{
}

Beautifly::Beautifly(int level) : Pokemon(level)
{
	this->Init(60, 61);
	//
	this->m_name = "Beautifly";
	this->m_type = MyObject::TYPE_FLYING;
	this->LearnSkill(new EnergyBall());
	this->LearnSkill(new Gust());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Beautifly::~Beautifly()
{
}