#include "Conversation.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <dos.h>
#include "ResourceManager.h"

void Converstation::Init(cocos2d::Layer * layer)
{
	this->m_messageBox = ResourceManager::GetInstance()->GetSpriteById(130);
	auto scale_x = 0.7;
	auto scale_y = 0.7;
	m_messageBox->setScaleX(scale_x);
	m_messageBox->setScaleY(scale_y);
	m_messageBox->setPosition(Director::getInstance()->getVisibleSize().width / 1.88, Director::getInstance()->getVisibleSize().height/4);
	layer->addChild(m_messageBox, 10);

	this->m_labelLog = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelLog->setAnchorPoint(Vec2::ZERO);
	this->m_labelLog->setScale(1.5);
	this->m_labelLog->setTextColor(Color4B::BLACK);
	this->m_labelLog->setString("What will you do?");
	this->m_labelLog->setPosition(this->m_messageBox->getContentSize().width * scale_x / 10, this->m_messageBox->getContentSize().height * scale_y / 1.2);
	this->m_messageBox->addChild(this->m_labelLog);
}

Converstation::Converstation(cocos2d::Layer * layer)
{
	Init(layer);
}

void Converstation::LogSetOpacity(GLubyte opacity)
{
	for (int i = 0; i < this->m_labelLog->getStringLength(); i++)
	{
		auto letter = this->m_labelLog->getLetter(i);
		if (letter != nullptr)
		{
			letter->setOpacity(opacity);
		}
	}
}

Converstation::~Converstation()
{

}