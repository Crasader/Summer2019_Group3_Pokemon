#include"Trainer.h"
#include"ResourceManager.h"






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
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(102);
	this->m_spriteFront->removeFromParent();
	this->m_spriteFront->setScale(2);
	this->m_spriteFront->setAnchorPoint(Vec2(0.5, 0));
	layer->addChild(this->m_spriteFront, 10);
}

void Trainer::walkLeft()
{
	auto moveLeft = MoveBy::create(1.125f, Vec2(-35, 0));
	auto animateLeft = ResourceManager::GetInstance()->GetAnimateById(92);
	auto spawn = Spawn::create(animateLeft, moveLeft, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(2);
	this->m_spriteFront->runAction(repeat);

}

void Trainer::walkRight()
{
	auto moveRight = MoveBy::create(1.125f, Vec2(35, 0));
	auto animateRight = ResourceManager::GetInstance()->GetAnimateById(93);
	auto spawn = Spawn::create(animateRight, moveRight, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(3);
	this->m_spriteFront->runAction(repeat);
}

void Trainer::walkUp()
{
	//this->m_spriteFront->setPosition(Vec2(this->m_spriteFront->getPosition().x, this->m_spriteFront->getPosition().y + 1));
	auto moveUp = MoveBy::create(1.125f, Vec2(0, 35));
	auto animateUp = ResourceManager::GetInstance()->GetAnimateById(90);
	auto spawn = Spawn::create(animateUp,moveUp, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(0);
	this->m_spriteFront->runAction(repeat);
}

void Trainer::walkDown()
{
	auto moveDown = MoveBy::create(1.125f, Vec2(0, -35));
	auto animateDown = ResourceManager::GetInstance()->GetAnimateById(91);
	auto spawn = Spawn::create(animateDown, moveDown, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(1);
	this->m_spriteFront->runAction(repeat);
}


Sprite * Trainer::GetSprite()
{
	return this->m_spriteFront;
}
