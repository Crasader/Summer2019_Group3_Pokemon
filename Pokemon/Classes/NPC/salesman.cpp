#include "salesman.h"

salesman::salesman(Scene * scene)
{
	this->Init();
	//this->m_spriteFront->setPosition();
	//this->m_spriteFront->setScale();
	scene->addChild(this->m_spriteFront);
}

salesman::~salesman()
{
}

void salesman::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(0);
}

void salesman::Update(float deltaTime)
{
}
