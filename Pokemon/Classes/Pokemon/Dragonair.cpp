#include "Dragonair.h"
#include "Dragonite.h"
#define hp 61
#define atk 84
#define def 65
#define speed 70

Dragonair::Dragonair()
{
}

Dragonair::Dragonair(int level) : Pokemon(level)
{
	this->Init(8, 9);
	//
	this->m_name = "Dragonair";
	this->m_type = MyObject::TYPE_DRAGON;
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Dragonair::~Dragonair()
{
}

Pokemon * Dragonair::Evolve()
{
	if (true)
	{
		this->m_evolved = true;
		return new Dragonite(this);
	}
	else
	{
		return nullptr;
	}
}
