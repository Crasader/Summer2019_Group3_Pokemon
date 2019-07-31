#include"Gust.h"

Gust::Gust()
{
	this->Init();
}

Gust::~Gust()
{
}

void Gust::Init()
{
	this->AddAnimation(102);
	this->GetAnimation()->setDelayPerUnit(0.08);
	this->SetScale(1.5);
	Skill::SetName("Gust");
	Skill::SetTypeName("Flying");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(MyObject::TYPE_FLYING);
	Skill::SetCurrentPP(20);
}

void Gust::Run(Vec2 position)
{
	this->m_spriteFront->setVisible(true);
	auto old_position = this->m_spriteFront->getPosition();
	auto moveTo = MoveTo::create(0.8, position);
	auto animate = Animate::create(this->m_animation);
	auto finished = CallFunc::create([this, old_position]() {
		this->m_spriteFront->setPosition(old_position);
		this->m_spriteFront->setVisible(false);
		this->m_state = true;
	});
	auto spawn = Spawn::create(Repeat::create(animate, 2), moveTo, nullptr);
	auto sequence = Sequence::create(spawn, finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}