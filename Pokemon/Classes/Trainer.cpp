#include "Trainer.h"
#include "ResourceManager.h"
#include "Pokemon/Squirtle.h"

list<Pokemon*> Trainer::m_Pokemons;

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
	this->m_spriteFront->setScale(1.5f);
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

void Trainer::AddPokemon(Pokemon *pokemon)
{
	Trainer::m_Pokemons.push_back(pokemon);
}

void Trainer::walkLeft()
{
	auto moveLeft = MoveBy::create(1.125f, Vec2(-75, 0));
	auto animateLeft = Animate::create(left);
	auto spawn = Spawn::create(animateLeft, moveLeft, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(2);
	m_spriteFront->runAction(repeat);
}

void Trainer::walkRight()
{
	auto moveRight = MoveBy::create(1.125f, Vec2(75, 0));
	auto animateRight = Animate::create(right);
	auto spawn = Spawn::create(animateRight, moveRight, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(3);
	this->m_spriteFront->runAction(repeat);
}

void Trainer::walkUp()
{
	auto moveUp = MoveBy::create(1.125f, Vec2(0, 75));
	auto animateUp = Animate::create(up);
	auto spawn = Spawn::create(animateUp,moveUp, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(0);
	m_spriteFront->runAction(repeat);
}

void Trainer::walkDown()
{
	auto moveDown = MoveBy::create(1.125f, Vec2(0, -75));
	auto animateDown = Animate::create(down);
	auto spawn = Spawn::create(animateDown, moveDown, nullptr);
	auto repeat = RepeatForever::create(spawn);
	repeat->setTag(1);
	this->m_spriteFront->runAction(repeat);
}
