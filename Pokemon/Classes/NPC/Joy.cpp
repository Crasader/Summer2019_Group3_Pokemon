#include "Joy.h"

Joy::Joy(Scene * scene)
{
	this->Init();
	//this->m_spriteFront->setPosition();
	//this->m_spriteFront->setScale();
	scene->addChild(this->m_spriteFront);
}

Joy::~Joy()
{
}

void Joy::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(0);
}

void Joy::Update(float deltaTime)
{
}
