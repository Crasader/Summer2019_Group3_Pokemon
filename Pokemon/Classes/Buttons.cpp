#include "Buttons.h"
#include "ResourceManager.h"

Buttons* Buttons::m_button = NULL;

Buttons::Buttons()
{
	m_down = ResourceManager::GetInstance()->GetButtonById(1);//thay id khac
	m_up = ResourceManager::GetInstance()->GetButtonById(4);
	m_left = ResourceManager::GetInstance()->GetButtonById(2);
	m_right = ResourceManager::GetInstance()->GetButtonById(3);
	m_down->setPosition(Vec2(100, 70));
	m_up->setPosition(Vec2(100, 130));
	m_left->setPosition(Vec2(70, 100));
	m_right->setPosition(Vec2(130, 100));
	m_down->setScale(0.4f);
	m_up->setScale(0.4f);
	m_left->setScale(0.4f);
	m_right->setScale(0.4f);
}


Buttons::~Buttons()
{
}

Buttons * Buttons::getIntance()
{
	if (!m_button) {
		m_button = new Buttons();
	}
	return m_button;
}

Button * Buttons::GetButtonUp()
{
	return m_up;
}

Button * Buttons::GetButtonLeft()
{
	return m_left;
}

Button * Buttons::GetButtonRight()
{
	return m_right;
}

Button * Buttons::GetButtonDown()
{
	return m_down;
}
