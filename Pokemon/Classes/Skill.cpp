#include "Skill.h"

Skill::Skill()
{
}

Skill::~Skill()
{
}

void Skill::SetPower(int x)
{
	m_power = x;
}

void Skill::SetPP(int y)
{
	m_pp = y;
}

void Skill::SetMaxPP(int m)
{
	m_maxpp = m;
}

void Skill::SetName(string n)
{
	m_name = n;
}

void Skill::SetType(string st)
{
	m_type = st;
}

void Skill::SetIdType(int it)
{
	m_idtype = it;
}

int Skill::GetMaxPP()
{
	return m_maxpp;
}

string Skill::GetName()
{
	return m_name;
}

string Skill::GetType()
{
	return m_type;
}

void Skill::SetState(bool state)
{
	this->m_state = state;
}

bool Skill::GetState()
{
	return this->m_state;
}

void Skill::AddAnimate(int id)
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(id);
	this->m_spriteFront->setAnchorPoint(Vec2(0.5, 0));
	this->m_spriteFront->setVisible(false);
	this->m_animation = ResourceManager::GetInstance()->GetAnimationById(id);
	this->m_animation->setDelayPerUnit(0.05);
}

void Skill::RunAnimate()
{
	this->m_spriteFront->setVisible(true);
	auto animate = Animate::create(this->m_animation);
	auto finished = CallFunc::create([this]() {
		this->m_state = true;
	});
	auto sequence = Sequence::create(animate, DelayTime::create(1), finished, nullptr);
	sequence->setTag(10);
	this->m_spriteFront->runAction(sequence);
}

void Skill::SetVisible(bool visible)
{
	this->m_spriteFront->setVisible(visible);
}

int Skill::GetPower()
{
	return m_power;
}

int Skill::GetPP()
{
	return m_pp;
}

int Skill::GetIdType()
{
	return m_idtype;
}