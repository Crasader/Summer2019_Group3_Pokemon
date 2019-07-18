#include "Pokemon.h"



Pokemon::Pokemon()
{
}


Pokemon::~Pokemon()
{
}

void Pokemon::Init()
{
}

void Pokemon::Init(int id_front, int id_back)
{
	//
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(id_front);
	this->m_spriteFront->setScale(2.5);
	this->m_spriteFront->setAnchorPoint(Vec2(0.5, 0));
	auto animateFront = ResourceManager::GetInstance()->GetAnimateById(id_front)->clone();
	this->m_spriteFront->runAction(RepeatForever::create(animateFront));
	auto bodyFront = PhysicsBody::createBox(this->m_spriteFront->getContentSize());
	this->m_spriteFront->setPhysicsBody(bodyFront);
	//
	this->m_spriteBack = ResourceManager::GetInstance()->GetSpriteById(id_back);
	this->m_spriteBack->setScale(2.5);
	this->m_spriteBack->setAnchorPoint(Vec2(0.5, 0));
	auto animateBack = ResourceManager::GetInstance()->GetAnimateById(id_back)->clone();
	this->m_spriteBack->runAction(RepeatForever::create(animateBack));
	auto bodyBack = PhysicsBody::createBox(this->m_spriteBack->getContentSize());
	this->m_spriteBack->setPhysicsBody(bodyBack);
}

void Pokemon::Update(float deltaTime)
{
}

Pokemon * Pokemon::Evolve()
{
	return nullptr;
}

int Pokemon::GetID()
{
	return this->m_id;
}

void Pokemon::LevelUp()
{
	this->m_level += 1;
	this->m_maxHealth += 10;
	this->m_currentHealth += 10;
	this->m_attack += 2;
	this->m_defense += 4;
	this->m_currentExp = 0;
	this->m_maxExp += 2;
}

string Pokemon::GetName()
{
	return this->m_name;
}

void Pokemon::SetName(string name)
{
	this->m_name = name;
}

int Pokemon::GetType()
{
	return this->m_type;
}

void Pokemon::SetType(int type)
{
	this->m_type = type;
}


int Pokemon::GetCurrentHP()
{
	return this->m_currentHealth;
}

void Pokemon::SetCurrentHP(int health)
{
	this->m_currentHealth = health;
}


int Pokemon::GetMaxHP()
{
	return this->m_maxHealth;
}

void Pokemon::SetMaxHP(int maxhealth)
{
	this->m_maxHealth = maxhealth;
}
int Pokemon::GetLevel()
{
	return this->m_level;
}

void Pokemon::SetLevel(int level)
{
	for (int i = this->m_level; i < level; i++)
	{
		this->LevelUp();
	}
}

int Pokemon::GetAtk()
{
	return this->m_attack;
}

void Pokemon::SetAtk(int atk)
{
	this->m_attack = atk;
}

int Pokemon::GetDef()
{
	return this->m_defense;
}

void Pokemon::SetDef(int def)
{
	this->m_defense = def;
}

int Pokemon::GetAtkSpeed()
{
	return this->m_attackSpeed;
}

void Pokemon::SetAtkSpeed(int atkSpeed)
{
	this->m_attackSpeed = atkSpeed;
}

int Pokemon::GetCurrentExp()
{
	return this->m_currentExp;
}

void Pokemon::SetCurrentExp(int exp)
{
	this->m_currentExp = exp;
}

int Pokemon::GetMaxExp()
{
	return this->m_maxExp;
}

void Pokemon::SetMaxExp(int exp)
{
	this->m_maxExp = exp;
}