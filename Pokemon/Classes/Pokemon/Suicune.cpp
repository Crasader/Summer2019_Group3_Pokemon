#include "Suicune.h"
#define hp 100
#define atk 75
#define def 90
#define speed 85

Suicune::Suicune()
{
}

Suicune::Suicune(int level) : Pokemon(level)
{
	this->Init(48, 49);
	//
	this->m_name = "Suicune";
	this->m_type = MyObject::TYPE_WATER;
	this->LearnSkill(new Bite());
	this->LearnSkill(new WaterPulse());
	this->LearnSkill(new Surf());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Suicune::~Suicune()
{
}