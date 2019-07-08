#include "Charmander.h"



Charmander::Charmander()
{
	this->Init();
	//
	this->m_name = "Charmander";
	this->m_level = 5;
	this->m_health = 40 + ((this->m_level - 1) * 10);
	this->m_attack = 52 + ((this->m_level - 1) * 2);
	this->m_defense = 43 + ((this->m_level - 1) * 4);
	this->m_attackSpeed = 65 + ((this->m_level - 1) * 1);
	this->m_currentExp = 0;
	this->m_maxExp = 2 + ((this->m_level - 1) * 2);
}


Charmander::~Charmander()
{
}

void Charmander::Init()
{
	//
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(4);
	this->m_spriteFront->setScale(2);
	this->m_spriteFront->setAnchorPoint(Vec2(0.5, 0));
	auto animateFront = ResourceManager::GetInstance()->GetAnimateById(4)->clone();
	this->m_spriteFront->runAction(RepeatForever::create(animateFront));
	auto bodyFront = PhysicsBody::createBox(this->m_spriteFront->getContentSize());
	this->m_spriteFront->setPhysicsBody(bodyFront);
	//
	this->m_spriteBack = ResourceManager::GetInstance()->GetSpriteById(5);
	this->m_spriteBack->setScale(2);
	this->m_spriteBack->setAnchorPoint(Vec2(0.5, 0));
	auto animateBack = ResourceManager::GetInstance()->GetAnimateById(5)->clone();
	this->m_spriteBack->runAction(RepeatForever::create(animateBack));
	auto bodyBack = PhysicsBody::createBox(this->m_spriteBack->getContentSize());
	this->m_spriteBack->setPhysicsBody(bodyBack);
}

void Charmander::Update(float deltaTime)
{
}

void Charmander::LevelUp()
{
	this->m_level += 1;
	this->m_health += 10;
	this->m_attack += 2;
	this->m_defense += 4;
	this->m_currentExp = 0;
	this->m_maxExp += 2;
}