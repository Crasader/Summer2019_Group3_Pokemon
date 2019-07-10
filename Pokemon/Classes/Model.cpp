#include "Model.h"
USING_NS_CC;

Model::Model()
{
}

Model::~Model()
{
}


void Model::setPosition(cocos2d::Vec2 pos)
{
	m_sprite->setPosition(pos);
}

void Model::setScale(float scale)
{
	m_sprite->setScale(scale);
}

cocos2d::Vec2 Model::getPosition()
{
	return m_sprite->getPosition();
}


Size Model::getContentSize()
{
	return m_sprite->getContentSize();
}