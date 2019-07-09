#include "Attack.h"

Attack::Attack()
{
}

Attack::~Attack()
{
}

void Attack::SetPower(int x)
{
	m_power = x;
}

void Attack::SetPP(int y)
{
	m_pp = y;
}

void Attack::SetMaxPP(int m)
{
	m_maxpp = m;
}

void Attack::SetName(string n)
{
	m_name = n;
}

void Attack::SetType(string st)
{
	m_type = st;
}

void Attack::SetIdType(int it)
{
	m_idtype = it;
}

int Attack::GetMaxPP()
{
	return m_maxpp;
}

string Attack::GetName()
{
	return m_name;
}

string Attack::GetType()
{
	return m_type;
}
int Attack::GetPower()
{
	return m_power;
}

int Attack::GetPP()
{
	return m_pp;
}

int Attack::GetIdType()
{
	return m_idtype;
}

