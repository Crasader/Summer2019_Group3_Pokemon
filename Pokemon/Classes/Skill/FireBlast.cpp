#include"FireBlast.h"

FireBlast::FireBlast()
{
	this->Init();
}

FireBlast::~FireBlast()
{
}

void FireBlast::Init()
{
	this->AddAnimation(99);
	this->SetScale(1.5);
	Skill::SetName("Fire Blast");
	Skill::SetType("Fire");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(2);
	Skill::SetPP(10);
}

void FireBlast::Run(Vec2 position)
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
	auto sequence = Sequence::create(moveTo, animate, DelayTime::create(0.5), finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}