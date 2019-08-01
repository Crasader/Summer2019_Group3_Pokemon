#include "Voltorb.h"
#define hp 40
#define atk 30
#define def 50
#define speed 100

Voltorb::Voltorb()
{
}

Voltorb::Voltorb(int level) : Pokemon(level)
{
	this->Init(52, 53);
	//
	this->m_name = "Voltorb";
	this->m_type = MyObject::TYPE_ELECTRIC;
	this->LearnSkill(new ThunderShock());
	this->LearnSkill(new Thunderbolt());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Voltorb::~Voltorb()
{
}