#include "Kirlia.h"
#include "Gardevoir.h"
#define hp 45
#define atk 50
#define def 50
#define speed 60

Kirlia::Kirlia()
{
}

Kirlia::Kirlia(int level) : Pokemon(level)
{
	this->Init(70, 71);
	//
	this->m_name = "Kirlia";
	this->m_type = MyObject::TYPE_GRASS;
	this->LearnSkill(new LeechSeed());
	this->LearnSkill(new EnergyBall());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Kirlia::Kirlia(Ralts * it)
{
	this->Init(70, 71);
	//
	this->m_name = "Kirlia";
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

Kirlia::~Kirlia()
{
}

Pokemon * Kirlia::Evolve()
{
	if (this->m_level >= 14)
	{
		this->LearnSkill(new RazorLeaf());
		this->m_evolved = true;
		return new Gardevoir(this);
	}
	else
	{
		return nullptr;
	}
}
