#include "Feebas.h"
#include "Milotic.h"
#define hp 40
#define atk 35
#define def 30
#define speed 80

Feebas::Feebas()
{
}

Feebas::Feebas(int level) : Pokemon(level)
{
	this->Init(18, 19);
	//
	this->m_name = "Feebas";
	this->m_type = MyObject::TYPE_WATER;
	this->LearnSkill(new Bubble());
	this->LearnSkill(new WaterPulse());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Feebas::~Feebas()
{
}

Pokemon * Feebas::Evolve()
{
	if (this->m_level >= 14)
	{
		this->LearnSkill(new DragonClaw());
		this->m_evolved = true;
		return new Milotic(this);
	}
	else
	{
		return nullptr;
	}
}