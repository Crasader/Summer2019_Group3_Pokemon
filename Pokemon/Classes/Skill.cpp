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

