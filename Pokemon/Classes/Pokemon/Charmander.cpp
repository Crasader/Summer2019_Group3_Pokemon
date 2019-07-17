#include "Charmander.h"
#include "Charmeleon.h"
#define hp 40
#define atk 52
#define def 43
#define speed 65


Charmander::Charmander()
{
	this->Init(4, 5);
	//
	this->m_name = "Charmander";
	this->m_type = MyObject::TYPE_FIRE;
	this->m_skills = { new Tackle(), new FireBlast(), nullptr };
	this->m_level = 5;
	this->m_maxHealth = hp + ((this->m_level - 1) * 10);
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = atk + ((this->m_level - 1) * 2);
	this->m_defense = def + ((this->m_level - 1) * 4);
	this->m_attackSpeed = speed + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}


Charmander::~Charmander()
{
}

Pokemon * Charmander::Evolve()
{
	if (this->m_level >= 10)
	{
		return new Charmeleon(this);
	}
	else
	{
		return nullptr;
	}
}