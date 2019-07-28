#include "Bubble.h"

Bubble::Bubble()
{
	this->Init();
}

Bubble::~Bubble()
{
}

void Bubble::Init()
{
	this->AddAnimation(93);
	this->GetAnimation()->setDelayPerUnit(0.1);
	this->SetScale(1.5);
	Skill::SetName("Bubble");
	Skill::SetTypeName("Water");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_WATER);
	Skill::SetCurrentPP(35);
}

void Bubble::Run(Vec2 position)
{
	this->m_spriteFront->setVisible(true);
	auto old_position = this->m_spriteFront->getPosition();
	auto moveTo = MoveTo::create(1, Vec2(position.x, position.y + 15));
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