#include "Pidgeotto.h"
#include "Pidgeot.h"
#define hp 63
#define atk 60
#define def 55
#define speed 71

Pidgeotto::Pidgeotto()
{
}

Pidgeotto::Pidgeotto(int level) : Pokemon(level)
{
	this->Init(76, 77);
	//
	this->m_name = "Pidgeotto";
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

Pidgeotto::Pidgeotto(Pidgey * it)
{
	this->Init(76, 77);
	//
	this->m_name = "Pidgeotto";
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

Pidgeotto::~Pidgeotto()
{
}

Pokemon * Pidgeotto::Evolve()
{
	if (this->m_level >= 14)
	{
		this->LearnSkill(new WingAttack());
		this->m_evolved = true;
		return new Pidgeot(this);
	}
	else
	{
		return nullptr;
	}
}
