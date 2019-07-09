#include "RouteNPC.h"
#include "Pokemon.h"
#include "Pokemon\Charmander.h"

RouteNPC::RouteNPC(Layer * layer)
{
	this->Init();
	layer->addChild(this->m_spriteFront);
}

RouteNPC::~RouteNPC()
{
}

void RouteNPC::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(46);
}

void RouteNPC::Update(float deltaTime)
{
}
