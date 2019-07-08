#include "MyObject.h"



MyObject::MyObject()
{
}


MyObject::~MyObject()
{
	this->m_spriteFront->release();
	this->m_spriteBack->release();
}

Sprite * MyObject::GetSpriteBack()
{
	return this->m_spriteBack;
}

Sprite * MyObject::GetSpriteFront()
{
	return this->m_spriteFront;
}