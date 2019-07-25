#include "WaterPulse.h"

WaterPulse::WaterPulse()
{
	this->Init();
}

WaterPulse::~WaterPulse()
{
}

void WaterPulse::Init()
{
	this->AddAnimation(116);
	this->SetScale(0.3);
	Skill::SetName("Water Pulse");
	Skill::SetTypeName("Water");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(MyObject::TYPE_WATER);
	Skill::SetCurrentPP(20);
}

void WaterPulse::Run(Vec2 position)
{
	this->m_spriteFront->setVisible(true);
	auto old_position = this->m_spriteFront->getPosition();
	auto moveTo = MoveTo::create(0.8, position);
	auto animate = Animate::create(this->m_animation);
	auto scaleTo = ScaleTo::create(0.8, 1);
	auto finished = CallFunc::create([this, old_position]() {
		this->m_spriteFront->setPosition(old_position);
		this->m_spriteFront->setVisible(false);
		this->SetScale(0.3);
		this->m_state = true;
	});
	auto spawn = Spawn::create(animate, scaleTo, moveTo, nullptr);
	auto sequence = Sequence::create(spawn, finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}