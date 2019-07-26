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
	this->GetAnimation()->setDelayPerUnit(0.1);
	this->SetScale(1.6);
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
	this->m_spriteFront->setPosition(position.x - 20, position.y);
	auto animate = Animate::create(this->m_animation);
	auto moveBy = MoveBy::create(1, Vec2(50, 0));
	auto finished = CallFunc::create([this, old_position]() {
		this->m_spriteFront->setPosition(old_position);
		this->m_spriteFront->setVisible(false);
		this->m_state = true;
	});
	auto sequence = Sequence::create(Spawn::create(Repeat::create(animate, 2), moveBy, nullptr), finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}