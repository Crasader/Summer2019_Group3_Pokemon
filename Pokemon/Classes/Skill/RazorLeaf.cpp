#include"RazorLeaf.h"

RazorLeaf::RazorLeaf()
{
	this->Init();
}

RazorLeaf::~RazorLeaf()
{
}

void RazorLeaf::Init()
{
	this->AddAnimation(105);
	this->SetScale(3.5);
	Skill::SetName("Razor Leaf");
	Skill::SetType("Grass");
	Skill::SetPower(60);
	Skill::SetMaxPP(20);
	Skill::SetIdType(4);
	Skill::SetPP(20);
}

void RazorLeaf::Run(Vec2 position)
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