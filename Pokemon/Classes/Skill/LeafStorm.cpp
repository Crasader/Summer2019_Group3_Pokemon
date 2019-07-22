#include "LeafStorm.h"

LeafStorm::LeafStorm()
{
	this->Init();
}

LeafStorm::~LeafStorm()
{
}

void LeafStorm::Init()
{
	this->AddAnimation(107);
	this->SetScale(1.5);
	Skill::SetName("Leaf Storm");
	Skill::SetTypeName("Grass");
	Skill::SetPower(100);
	Skill::SetMaxPP(5);
	Skill::SetIdType(MyObject::TYPE_GRASS);
	Skill::SetCurrentPP(5);
}

void LeafStorm::Run(Vec2 position)
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