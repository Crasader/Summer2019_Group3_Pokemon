#include "DrSamuelOak.h"

DrSamuelOak::DrSamuelOak(Scene * scene)
{
	this->Init();
	//this->m_spriteFront->setPosition();
	//this->m_spriteFront->setScale();
	scene->addChild(this->m_spriteFront);
}

DrSamuelOak::~DrSamuelOak()
{
}

void DrSamuelOak::Init()
{
	this->m_spriteFront = ResourceManager::GetInstance()->GetSpriteById(0);
}

void DrSamuelOak::Update(float deltaTime)
{
}
