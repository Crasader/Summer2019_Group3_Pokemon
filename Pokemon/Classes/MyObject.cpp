#include "MyObject.h"



MyObject::MyObject()
{
}


MyObject::~MyObject()
{
}

Sprite * MyObject::GetSprite()
{
	return this->m_sprite;
}