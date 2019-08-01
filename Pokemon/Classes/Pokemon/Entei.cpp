#include "Entei.h"
#define hp 95
#define atk 85
#define def 85
#define speed 100

Entei::Entei()
{
}

Entei::Entei(int level) : Pokemon(level)
{
	this->Init(16, 17);
	//
	this->m_name = "Entei";
	this->m_type = MyObject::TYPE_FIRE;
	this->LearnSkill(new Bite());
	this->LearnSkill(new FireBlast());
	this->LearnSkill(new BlastBurn());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Entei::~Entei()
{
}