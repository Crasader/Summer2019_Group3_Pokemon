#include "Squirtle.h"
#include "Wartortle.h"
#define hp 44
#define atk 48
#define def 65
#define speed 43

Squirtle::Squirtle()
{
}

Squirtle::Squirtle(int level) : Pokemon(level)
{
	this->Init(46, 47);
	//
	this->m_name = "Squirtle";
	this->m_type = MyObject::TYPE_WATER;
	this->LearnSkill(new WaterGun());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Squirtle::~Squirtle()
{
}

Pokemon * Squirtle::Evolve()
{
	if (this->m_level >= 8)
	{
		this->LearnSkill(new WaterPulse());
		this->m_evolved = true;
		return new Wartortle(this);
	}
	else
	{
		return nullptr;
	}
}