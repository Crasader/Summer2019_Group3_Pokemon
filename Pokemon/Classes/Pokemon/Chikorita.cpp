#include "Chikorita.h"
#include "Bayleef.h"
#define hp 45
#define atk 49
#define def 65
#define speed 45

Chikorita::Chikorita()
{
}

Chikorita::Chikorita(int level) : Pokemon(level)
{
	this->Init(64, 65);
	//
	this->m_name = "Chikorita";
	this->m_type = MyObject::TYPE_GRASS;
	this->LearnSkill(new LeechSeed());
	this->m_maxHealth += hp;
	this->m_currentHealth = this->m_maxHealth;
	this->m_attack += atk;
	this->m_defense += def;
	this->m_attackSpeed += speed;
	this->m_maxExp += 2;
}

Chikorita::~Chikorita()
{
}

Pokemon * Chikorita::Evolve()
{
	if (this->m_level >= 8)
	{
		this->LearnSkill(new RazorLeaf());
		this->m_evolved = true;
		return new Bayleef(this);
	}
	else
	{
		return nullptr;
	}
}