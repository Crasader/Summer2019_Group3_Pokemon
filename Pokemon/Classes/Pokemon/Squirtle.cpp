#include "Squirtle.h"
#include "Wartortle.h"

Squirtle::Squirtle()
{
	this->Init();
	//
	this->m_name = "Squirtle";
	this->m_level = 5;
	this->m_health = 44 + ((this->m_level - 1) * 10);
	this->m_attack = 48 + ((this->m_level - 1) * 2);
	this->m_defense = 65 + ((this->m_level - 1) * 4);
	this->m_attackSpeed = 43 + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}

Squirtle::~Squirtle()
{
}

void Squirtle::Init()
{
	//
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(46);
	this->m_spriteFront->setScale(2);
	this->m_spriteFront->setAnchorPoint(Vec2(0.5, 0));
	auto animateFront = ResourceManager::GetInstance()->GetAnimateById(46)->clone();
	this->m_spriteFront->runAction(RepeatForever::create(animateFront));
	auto bodyFront = PhysicsBody::createBox(this->m_spriteFront->getContentSize());
	this->m_spriteFront->setPhysicsBody(bodyFront);
	//
	this->m_spriteBack = ResourceManager::GetInstance()->GetSpriteById(47);
	this->m_spriteBack->setScale(2);
	this->m_spriteBack->setAnchorPoint(Vec2(0.5, 0));
	auto animateBack = ResourceManager::GetInstance()->GetAnimateById(47)->clone();
	this->m_spriteBack->runAction(RepeatForever::create(animateBack));
	auto bodyBack = PhysicsBody::createBox(this->m_spriteBack->getContentSize());
	this->m_spriteBack->setPhysicsBody(bodyBack);
}

void Squirtle::Update(float deltaTime)
{
}

void Squirtle::LevelUp()
{
	this->m_level += 1;
	this->m_health += 10;
	this->m_attack += 2;
	this->m_defense += 4;
	this->m_currentExp = 0;
	this->m_maxExp += 2;
}

Pokemon * Squirtle::Evolve()
{
	return new Wartortle(this);
}