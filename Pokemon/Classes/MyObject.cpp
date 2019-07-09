#include "MyObject.h"



MyObject::MyObject()
{
}


MyObject::~MyObject()
{
	this->m_spriteFront->removeFromParentAndCleanup(true);
	this->m_spriteBack->removeFromParentAndCleanup(true);
}

Sprite * MyObject::GetSpriteBack()
{
	return this->m_spriteBack;
}

Sprite * MyObject::GetSpriteFront()
{
	return this->m_spriteFront;
}