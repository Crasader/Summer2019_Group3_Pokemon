#include"Thunder.h"

Thunder::Thunder()
{
	this->Init();
}

Thunder::~Thunder()
{
}

void Thunder::Init()
{
	this->AddAnimation(111);
	this->SetScale(1.5);
	Skill::SetName("Thunder");
	Skill::SetType("Electric");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(5);
	Skill::SetPP(5);
}

void Thunder::Run(Vec2 position)
{
	this->m_spriteFront->setVisible(true);
	auto old_position = this->m_spriteFront->getPosition();
	this->m_spriteFront->setPosition(position);
	auto animate = Animate::create(this->m_animation);
	auto finished = CallFunc::create([this, old_position]() {
		this->m_spriteFront->setPosition(old_position);
		this->m_spriteFront->setVisible(false);
		this->m_state = true;
	});
	auto sequence = Sequence::create(Repeat::create(animate, 2), finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}