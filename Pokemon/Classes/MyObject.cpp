#include "MyObject.h"



MyObject::MyObject()
{
}


MyObject::~MyObject()
{
}

Sprite * MyObject::GetSpriteBack()
{
	return this->m_spriteBack;
}

Sprite * MyObject::GetSpriteFront()
{
	return this->m_spriteFront;
}