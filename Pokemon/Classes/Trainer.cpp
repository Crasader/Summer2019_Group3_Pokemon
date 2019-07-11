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
	m_sprite = ResourceManager::GetInstance()->GetSpriteById(102);
	m_sprite->removeFromParent();
	m_sprite->setScale(2);
	m_sprite->setAnchorPoint(Vec2(0.5, 0));
	layer->addChild(m_sprite, 10);
}

void Trainer::walkLeft()
{
	auto moveLeft = MoveBy::create(1.125f, Vec2(-35, 0));
	auto animateLeft = ResourceManager::GetInstance()->GetAnimateById(92);
	auto spawn = Spawn::create(animateLeft, moveLeft, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(2);
	m_sprite->runAction(repeat);

}

void Trainer::walkRight()
{
	auto moveRight = MoveBy::create(1.125f, Vec2(35, 0));
	auto animateRight = ResourceManager::GetInstance()->GetAnimateById(93);
	auto spawn = Spawn::create(animateRight, moveRight, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(3);
	m_sprite->runAction(repeat);
}

void Trainer::walkUp()
{
	//m_sprite->setPosition(Vec2(m_sprite->getPosition().x, m_sprite->getPosition().y + 1));
	auto moveUp = MoveBy::create(1.125f, Vec2(0, 35));
	auto animateUp = ResourceManager::GetInstance()->GetAnimateById(90);
	auto spawn = Spawn::create(animateUp,moveUp, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(0);
	m_sprite->runAction(repeat);
}

void Trainer::walkDown()
{
	auto moveDown = MoveBy::create(1.125f, Vec2(0, -35));
	auto animateDown = ResourceManager::GetInstance()->GetAnimateById(91);
	auto spawn = Spawn::create(animateDown, moveDown, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(1);
	m_sprite->runAction(repeat);
}

void Trainer::setPosition(cocos2d::Vec2 pos)
{
	m_sprite->setPosition(pos);
}

cocos2d::Vec2 Trainer::getPosition()
{
	return m_sprite->getPosition();
	
}

Sprite * Trainer::GetSprite()
{
	return m_sprite;
}
