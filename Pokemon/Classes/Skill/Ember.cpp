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
	Attack::SetName("Ember");
	Attack::SetType("Fire");
	Attack::SetPower(40);
	Attack::SetMaxPP(35);
	Attack::SetIdType(2);
	Attack::SetPP(35);
}

