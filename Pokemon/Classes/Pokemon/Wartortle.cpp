#include "Wartortle.h"
#include "Blastoise.h"
#define hp 40
#define atk 52
#define def 43
#define speed 65

Wartortle::Wartortle()
{
	this->Init(56, 57);
}

Wartortle::Wartortle(int level) : Pokemon(level)
{
	this->Init(56, 57);
	//
	this->m_name = "Wartortle";
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

Wartortle::Wartortle(Squirtle * it)
{
	this->Init(56, 57);
	//
	this->m_name = "Wartortle";
	this->m_type = it->GetType();
	this->m_listSkill = { it->GetSkillById(0), it->GetSkillById(1), it->GetSkillById(2) };
	this->m_level = it->GetLevel();
	this->m_maxHealth = it->GetMaxHP() + 15;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack = it->GetAtk() + 5;
	this->m_defense = it->GetDef() + 5;
	this->m_attackSpeed = it->GetAtkSpeed() + 2;
	this->m_currentExp = 0;
	this->m_maxExp = it->GetMaxExp();
	delete it;
}

Wartortle::~Wartortle()
{
}

Pokemon * Wartortle::Evolve()
{
	if (this->m_level >= 15)
	{
		this->LearnSkill(new Surf());
		this->m_evolved = true;
		return new Blastoise(this);
	}
	else
	{
		return nullptr;
	}
}