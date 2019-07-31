#include "Snorlax.h"
#define hp 160
#define atk 80
#define def 75
#define speed 30

Snorlax::Snorlax()
{
}

Snorlax::Snorlax(int level) : Pokemon(level)
{
	this->Init(44, 45);
	//
	this->m_name = "Snorlax";
	this->m_type = MyObject::TYPE_NORMAL;
	this->m_listSkill = { new Tackle(), new BodySlam(), new FirePunch() };
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Snorlax::~Snorlax()
{
}