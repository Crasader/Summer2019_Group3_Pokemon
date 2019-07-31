#include "Electrike.h"
#include "Manectric.h"
#define hp 40
#define atk 45
#define def 40
#define speed 65

Electrike::Electrike()
{
}

Electrike::Electrike(int level) : Pokemon(level)
{
	this->Init(14, 15);
	//
	this->m_name = "Electrike";
	this->m_type = MyObject::TYPE_ELECTRIC;
	this->LearnSkill(new QuickAttack());
	this->LearnSkill(new Spark());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Electrike::~Electrike()
{
}

Pokemon * Electrike::Evolve()
{
	if (this->m_level >= 10)
	{
		this->LearnSkill(new Thunder());
		this->m_evolved = true;
		return new Manectric(this);
	}
	else
	{
		return nullptr;
	}
}
