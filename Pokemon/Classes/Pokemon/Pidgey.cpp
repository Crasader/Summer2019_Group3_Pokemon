#include "Pidgey.h"
#include "Pidgeotto.h"
#define hp 40
#define atk 45
#define def 40
#define speed 56

Pidgey::Pidgey()
{
	this->Init(78, 79);
	//
	this->m_name = "Pidgey";
	this->m_type = MyObject::TYPE_FLYING;
	this->LearnSkill(new Peck());
	this->m_level = rand() % 2 + 1;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Pidgey::~Pidgey()
{
}

Pokemon * Pidgey::Evolve()
{
	if (this->m_level >= 8)
	{
		this->LearnSkill(new Gust());
		this->m_evolved = true;
		return new Pidgeotto(this);
	}
	else
	{
		return nullptr;
	}
}
