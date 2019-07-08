#include "Blastoise.h"

Blastoise::Blastoise()
{
	this->Init();
}

Blastoise::Blastoise(Wartortle * it)
{
	this->Init();
	//
	this->m_name = "Blastoise";
	this->m_level = it->GetLevel();
	this->m_health = it->GetHP() + 15;
	this->m_attack = it->GetAtk() + 5;
	this->m_defense = it->GetDef() + 5;
	this->m_attackSpeed = it->GetAtkSpeed() + 2;
	this->m_currentExp = 0;
	this->m_maxExp = it->GetMaxExp();
	delete it;
}

Blastoise::~Blastoise()
{
}

void Blastoise::Init()
{
	//
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(0);
	this->m_spriteFront->setScale(2);
	this->m_spriteFront->setAnchorPoint(Vec2(0.5, 0));
	auto animateFront = ResourceManager::GetInstance()->GetAnimateById(0)->clone();
	this->m_spriteFront->runAction(RepeatForever::create(animateFront));
	auto bodyFront = PhysicsBody::createBox(this->m_spriteFront->getContentSize());
	this->m_spriteFront->setPhysicsBody(bodyFront);
	//
	this->m_spriteBack = ResourceManager::GetInstance()->GetSpriteById(1);
	this->m_spriteBack->setScale(2);
	this->m_spriteBack->setAnchorPoint(Vec2(0.5, 0));
	auto animateBack = ResourceManager::GetInstance()->GetAnimateById(1)->clone();
	this->m_spriteBack->runAction(RepeatForever::create(animateBack));
	auto bodyBack = PhysicsBody::createBox(this->m_spriteBack->getContentSize());
	this->m_spriteBack->setPhysicsBody(bodyBack);
}

void Blastoise::Update(float deltaTime)
{
}

void Blastoise::LevelUp()
{
	this->m_level += 1;
	this->m_health += 10;
	this->m_attack += 2;
	this->m_defense += 4;
	this->m_currentExp = 0;
	this->m_maxExp += 2;
}