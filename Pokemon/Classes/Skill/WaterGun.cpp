#include"WaterGun.h"

WaterGun::WaterGun()
{
	this->Init();
}

WaterGun::~WaterGun()
{
}

void WaterGun::Init()
{
	this->AddAnimation(115);
	this->SetScale(3.5);
	Skill::SetName("Water Gun");
	Skill::SetTypeName("Water");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_WATER);
	Skill::SetCurrentPP(35);
}

void WaterGun::Run(Vec2 position)
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
	auto spawn = Spawn::create(Repeat::create(animate, 3), moveTo, nullptr);
	auto sequence = Sequence::create(spawn, finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}