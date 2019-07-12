#include "Pidgeotto.h"
#include "Pidgeot.h"
#define hp 63
#define atk 55
#define def 53
#define speed 71

Pidgeotto::Pidgeotto()
{
}

Pidgeotto::Pidgeotto(Pidgey * it)
{
	this->Init(76, 77);
	//
	this->m_name = "Pidgeotto";
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
	if (true)
	{
		return new Pidgeot(this);
	}
	else
	{
		return nullptr;
	}
}
