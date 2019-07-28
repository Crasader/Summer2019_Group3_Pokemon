#include"Ember.h"

Ember::Ember()
{
	this->Init();
}

Ember::~Ember()
{
}

void Ember::Init()
{
	this->AddAnimation(97);
	this->SetScale(3);
	Skill::SetName("Ember");
	Skill::SetTypeName("Fire");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(MyObject::TYPE_FIRE);
	Skill::SetCurrentPP(35);
}

void Ember::Run(Vec2 position)
{
	this->m_spriteFront->setVisible(true);
	auto old_position = this->m_spriteFront->getPosition();
	this->m_spriteFront->setPosition(position);
	auto animate = Animate::create(this->m_animation);
	auto moveBy = MoveBy::create(0.5, Vec2(20, 0));
	auto finished = CallFunc::create([this, old_position]() {
		this->m_spriteFront->setPosition(old_position);
		this->m_spriteFront->setVisible(false);
		this->m_state = true;
	});
	auto sequence = Sequence::create(Spawn::create(animate, moveBy, nullptr), finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}