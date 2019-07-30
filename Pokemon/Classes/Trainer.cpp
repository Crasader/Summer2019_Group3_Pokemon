#include "Trainer.h"
#include "ResourceManager.h"
#include "Pokemon/Squirtle.h"


Trainer::Trainer()
{
}

Trainer::Trainer(cocos2d::Layer * layer)
{
	Init(layer);
}

Trainer::~Trainer()
{
}

void Trainer::Init(cocos2d::Layer* layer)
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(118);
	this->m_spriteFront->removeFromParent();
	this->m_spriteFront->setScale(2);
	this->m_spriteFront->setAnchorPoint(Vec2(0.5, 0));
	layer->addChild(this->m_spriteFront, 10);
	left = ResourceManager::GetInstance()->GetAnimationById(120);
	left->setDelayPerUnit(0.3);
	left->setRestoreOriginalFrame(true);
	right = ResourceManager::GetInstance()->GetAnimationById(121);
	right->setDelayPerUnit(0.3);
	right->setRestoreOriginalFrame(true);
	up = ResourceManager::GetInstance()->GetAnimationById(118);
	up->setDelayPerUnit(0.3);
	up->setRestoreOriginalFrame(true);
	down = ResourceManager::GetInstance()->GetAnimationById(119);
	down->setDelayPerUnit(0.3);
	down->setRestoreOriginalFrame(true);
}

void Trainer::WalkLeft()
{
	auto moveLeft =RepeatForever::create(MoveBy::create(1, Vec2(-80, 0)));
	auto animateLeft = RepeatForever::create(Animate::create(left));
	moveLeft->setTag(4);
	animateLeft->setTag(5);
	this->m_spriteFront->runAction(animateLeft);
	this->m_spriteFront->runAction(moveLeft);
}

void Trainer::WalkRight()
{
	auto moveRight = RepeatForever::create(MoveBy::create(1, Vec2(80, 0)));
	auto animateRight = RepeatForever::create(Animate::create(right));
	moveRight->setTag(6);
	animateRight->setTag(7);
	this->m_spriteFront->runAction(animateRight);
	this->m_spriteFront->runAction(moveRight);
}

void Trainer::WalkUp()
{
	auto moveUp = RepeatForever::create(MoveBy::create(1, Vec2(0, 80)));
	auto animateUp = RepeatForever::create(Animate::create(up));
	moveUp->setTag(0);
	animateUp->setTag(1);
	this->m_spriteFront->runAction(animateUp);
	this->m_spriteFront->runAction(moveUp);
}

void Trainer::WalkDown()
{
	auto moveDown = RepeatForever::create(MoveBy::create(1, Vec2(0, -80)));
	auto animateDown = RepeatForever::create(Animate::create(down));
	moveDown->setTag(2);
	animateDown->setTag(3);
	this->m_spriteFront->runAction(animateDown);
	this->m_spriteFront->runAction(moveDown);
}

void Trainer::StopWalkUp()
{
	this->m_spriteFront->stopActionByTag(0);
	this->m_spriteFront->stopActionByTag(1);
	this->m_spriteFront->setTexture("res/Trainer/walkup/1.png");
}

void Trainer::StopWalkDown()
{
	this->m_spriteFront->stopActionByTag(2);
	this->m_spriteFront->stopActionByTag(3);
	this->m_spriteFront->setTexture("res/Trainer/walkdown/1.png");
}

void Trainer::StopWalkLeft()
{
	this->m_spriteFront->stopActionByTag(4);
	this->m_spriteFront->stopActionByTag(5);
	this->m_spriteFront->setTexture("res/Trainer/walkleft/1.png");
}

void Trainer::StopWalkRight()
{
	this->m_spriteFront->stopActionByTag(6);
	this->m_spriteFront->stopActionByTag(7);
	this->m_spriteFront->setTexture("res/Trainer/walkright/1.png");
}