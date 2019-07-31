#include "Skymin.h"
#define hp 40
#define atk 52
#define def 43
#define speed 65

Skymin::Skymin()
{
}

Skymin::Skymin(int level) : Pokemon(level)
{
	this->Init(84, 85);
	//
	this->m_name = "Skymin";
	this->m_type = MyObject::TYPE_GRASS;
	this->LearnSkill(new QuickAttack());
	this->LearnSkill(new RazorLeaf());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Skymin::~Skymin()
{
}