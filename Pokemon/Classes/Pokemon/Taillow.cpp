#include "Taillow.h"
#include "Swellow.h"
#define hp 40
#define atk 45
#define def 30
#define speed 85

Taillow::Taillow()
{
}

Taillow::Taillow(int level) : Pokemon(level)
{
	this->Init(88, 89);
	//
	this->m_name = "Taillow";
	this->m_type = MyObject::TYPE_FLYING;
	this->LearnSkill(new Peck());
	this->LearnSkill(new Gust());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Taillow::~Taillow()
{
}

Pokemon * Taillow::Evolve()
{
	if (this->m_level >= 10)
	{
		this->LearnSkill(new WingAttack());
		this->m_evolved = true;
		return new Swellow(this);
	}
	else
	{
		return nullptr;
	}
}