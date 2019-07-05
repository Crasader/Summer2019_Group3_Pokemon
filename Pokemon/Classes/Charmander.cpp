#include "Charmander.h"



Charmander::Charmander()
{
	this->Init();
}


Charmander::~Charmander()
{
}

void Charmander::Init()
{
	//
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(4);
	this->m_spriteFront->setScale(1.5);
	auto animateFront = ResourceManager::GetInstance()->GetAnimateById(4)->clone();
	this->m_spriteFront->runAction(RepeatForever::create(animateFront));
	//
	this->m_spriteBack = ResourceManager::GetInstance()->GetSpriteById(5);
	this->m_spriteBack->setScale(1.5);
	auto animateBack = ResourceManager::GetInstance()->GetAnimateById(5)->clone();
	this->m_spriteBack->runAction(RepeatForever::create(animateBack));
	//
}

void Charmander::Update(float deltaTime)
{
}
