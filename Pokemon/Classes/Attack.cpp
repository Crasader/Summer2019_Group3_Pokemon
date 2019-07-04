#include "Attack.h"

Attack::Attack()
{
}

Attack::~Attack()
{
}

int Attack::GetPower()
{
	return m_power;
}

int Attack::GetPP()
{
	return m_pp;
}

void Attack::SetPower(int x)
{
	m_power = x;
}

void Attack::SetPP(int y)
{
	m_pp = y;
}

