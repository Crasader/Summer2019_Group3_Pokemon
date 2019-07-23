#include"EnergyBall.h"

EnergyBall::EnergyBall()
{
	this->Init();
}

EnergyBall::~EnergyBall()
{
}

void EnergyBall::Init()
{
	this->SetAnimation(98);
	this->GetAnimation()->setDelayPerUnit(0.12);
	this->SetScale(1.5);
	Skill::SetName("Energy Ball");
	Skill::SetTypeName("Grass");
	Skill::SetPower(80);
	Skill::SetMaxPP(10);
	Skill::SetIdType(4);
	Skill::SetCurrentPP(10);
}

void EnergyBall::Run(Vec2 position)
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
	auto spawn = Spawn::create(animate, moveTo, nullptr);
	auto sequence = Sequence::create(spawn, finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}