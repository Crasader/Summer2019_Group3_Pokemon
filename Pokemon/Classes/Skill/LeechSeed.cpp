#include "LeechSeed.h"

LeechSeed::LeechSeed()
{
	this->Init();
}

LeechSeed::~LeechSeed()
{
}

void LeechSeed::Init()
{
	this->AddAnimation(114);
	this->GetAnimation()->setDelayPerUnit(0.3);
	this->SetScale(2);
	Skill::SetName("Leech Seed");
	Skill::SetTypeName("Grass");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_GRASS);
	Skill::SetCurrentPP(35);
}

void LeechSeed::Run(Vec2 position)
{
	this->m_spriteFront->setAnchorPoint(Vec2(0.5, 0.25));
	this->m_spriteFront->setVisible(true);
	auto old_position = this->m_spriteFront->getPosition();
	auto moveTo = MoveTo::create(0.8, position);
	auto animate = Animate::create(this->m_animation);
	auto finished = CallFunc::create([this, old_position]() {
		this->m_spriteFront->setPosition(old_position);
		this->m_spriteFront->setVisible(false);
		this->m_state = true;
	});
	auto sequence = Sequence::create(moveTo, animate, finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}