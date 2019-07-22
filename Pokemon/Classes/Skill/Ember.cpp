#include"Ember.h"

Ember::Ember()
{
}

Ember::~Ember()
{
}

void Ember::Init()
{
	Skill::SetName("Ember");
	Skill::SetTypeName("Fire");
	Skill::SetPower(40);
	Skill::SetMaxPP(35);
	Skill::SetIdType(2);
	Skill::SetCurrentPP(35);
}

