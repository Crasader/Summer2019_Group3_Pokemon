#include "Buttons.h"
#include "ResourceManager.h"
#include "Popup.h"
#include <iostream>
Buttons* Buttons::m_button = NULL;
int Buttons::state = 0;

Buttons::Buttons()
{
	m_up = ResourceManager::GetInstance()->GetButtonById(4);
	m_up->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_bag = ResourceManager::GetInstance()->GetButtonById(11);
	m_tips = ResourceManager::GetInstance()->GetButtonById(13);

	m_tips->setPosition(Vec2(30, 330));
	m_up->setPosition(Vec2(100, 100));
	m_bag->setPosition(Vec2(600,100));

	m_up->setScale(0.8f);
	m_up->setOpacity(100);
	m_tips->setScale(0.2f);
}


int Buttons::IsContainUp(Vec2 t, Trainer *mPlayer) {
	return (mPlayer->GetSpriteFront()->getBoundingBox().containsPoint(t));
}

void Buttons::ButtonListener(Trainer *&mPlayer)
{
	Vec2 movelo;
	Vec2 m_upPosition = m_up->getPosition();
	m_up->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			m_upPosition = m_up->getPosition();
			movelo = m_up->getTouchBeganPosition();
			float y = movelo.y -m_upPosition.y;
			float x = movelo.x - m_upPosition.x;
			float mAngle = atan2(y, x) * 180 / 3.14;
			if (mAngle > -45 && mAngle <= 45) {
				mPlayer->WalkRight();
				state = 2;
				break;
			}
			else if (mAngle > 45 && mAngle <= 135) {
				mPlayer->WalkUp();
				state = 1;
				break;
			}
			else if (mAngle > -135 && mAngle <= -45) {
				mPlayer->WalkDown();
				state = 4;
				break;
			}
			else {
				mPlayer->WalkLeft();
				state = 3;
				break;
			}
		}
		case ui::Widget::TouchEventType::MOVED:
		{
			m_upPosition = m_up->getPosition();
			movelo = m_up->getTouchMovePosition();
			if (m_up->getBoundingBox().containsPoint(movelo)) {
				Vec2 m_upPosition = m_up->getPosition();
				float y = movelo.y - m_upPosition.y;
				float x = movelo.x - m_upPosition.x;
				float mAngle = atan2(y, x) * 180 / 3.14;
				if (mAngle > -45 && mAngle <= 45) {
					if (state == 1) {
						mPlayer->StopWalkUp();
					}
					if (state == 3) {
						mPlayer->StopWalkLeft();
					}
					if (state == 4) {
						mPlayer->StopWalkDown();
					}
					mPlayer->isMoveRight = 1;
					mPlayer->isMoveUp = 0;
					mPlayer->isMoveDown = 0;
					mPlayer->isMoveLeft = 0;
					state = 2;
				}
				else if (mAngle > 45 && mAngle <= 135) {
					mPlayer->isMoveRight = 0;
					mPlayer->isMoveUp = 1;
					mPlayer->isMoveDown = 0;
					mPlayer->isMoveLeft = 0;
					if (state == 2) {
						mPlayer->StopWalkRight();
					}
					if (state == 3) {
						mPlayer->StopWalkLeft();
					}
					if (state == 4) {
						mPlayer->StopWalkDown();
					}
					state = 1;
				}
				else if (mAngle > -135 && mAngle <= -45) {
					mPlayer->isMoveRight = 0;
					mPlayer->isMoveUp = 0;
					mPlayer->isMoveDown = 1;
					mPlayer->isMoveLeft = 0;
					if (state == 1) {
						mPlayer->StopWalkUp();
					}
					if (state == 3) {
						mPlayer->StopWalkLeft();
					}
					if (state == 2) {
						mPlayer->StopWalkRight();
					}
					state = 4;
				}
				else {
					mPlayer->isMoveRight = 0;
					mPlayer->isMoveUp = 0;
					mPlayer->isMoveDown = 0;
					mPlayer->isMoveLeft = 1;
					mPlayer->isMoveRight = 1;
					if (state == 1) {
						mPlayer->StopWalkUp();
					}
					if (state == 2) {
						mPlayer->StopWalkRight();
					}
					if (state == 4) {
						mPlayer->StopWalkDown();
					}
					state = 3;
				}
			}
			else {
				mPlayer->isMoveRight = 0;
				mPlayer->isMoveUp = 0;
				mPlayer->isMoveLeft = 0;
				mPlayer->isMoveDown = 0;

				if (state == 1) {
					mPlayer->StopWalkUp();
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkup/1.png");
					state = 0;
				}
				else if (state == 2) {
					mPlayer->StopWalkRight();
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkright/1.png");
					state = 0;
				}
				else if (state == 3) {
					mPlayer->StopWalkLeft();
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkleft/1.png");
					state = 0;
				}
				else if (state == 4) {
					mPlayer->StopWalkDown();
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkdown/1.png");
					state = 0;
				}
			}
			break;
		}
		default:
		{
			mPlayer->isMoveRight = 0;
			mPlayer->isMoveUp = 0;
			mPlayer->isMoveLeft = 0;
			mPlayer->isMoveDown = 0;

			if (state == 1) {
				mPlayer->StopWalkUp();
				mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkup/1.png");
				state = 0;
			}
			else if (state == 2) {
				mPlayer->StopWalkRight();
				mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkright/1.png");
				state = 0;
			}
			else if (state == 3) {
				mPlayer->StopWalkLeft();
				mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkleft/1.png");
				state = 0;
			}
			else if (state == 4) {
				mPlayer->StopWalkDown();
				mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkdown/1.png");
				state = 0;
			}
			break;
		}
		}
	});
}

float Buttons::Cos(Vec2 a, Vec2 b) {
	return Vec2::angle(a, b) * 180 / 3.14;
}

Buttons::~Buttons()
{
}

Buttons * Buttons::GetIntance()
{
	if (!m_button)
	{
		m_button = new Buttons();
	}
	return m_button;
}

Button * Buttons::GetButtonUp()
{
	return m_up;
}


Button * Buttons::GetButtonBag()
{
	return m_bag;
}

Button * Buttons::GetButtonTips()
{
	return m_tips;
}

void Buttons::Remove()
{
	m_up->removeFromParentAndCleanup(true);
	m_bag->removeFromParentAndCleanup(true);
	m_tips->removeFromParentAndCleanup(true);
	m_up->release();
	m_bag->release();
	m_tips->release();
	m_up = ResourceManager::GetInstance()->GetButtonById(4);
	m_bag = ResourceManager::GetInstance()->GetButtonById(11);
	m_tips = ResourceManager::GetInstance()->GetButtonById(13);
	m_up->setPosition(Vec2(100, 100));
	m_bag->setPosition(Vec2(600, 100));
	m_tips->setPosition(Vec2(30, 330));
	m_up->setScale(0.8f);
	m_up->setOpacity(100);
	m_tips->setScale(0.2f);
}

void Buttons::UpdateButton(float x, float y) {
	m_up->setPosition(Vec2(x , y));
	m_bag->setPosition(Vec2(x + 400, y));
	m_tips->setPosition(Vec2(x +200 -330, y +100 +150));
}

void Buttons::SetTouchEnable()
{
	Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
	Buttons::GetIntance()->GetButtonDown()->setTouchEnabled(true);
	Buttons::GetIntance()->GetButtonLeft()->setTouchEnabled(true);
	Buttons::GetIntance()->GetButtonRight()->setTouchEnabled(true);
	Buttons::GetIntance()->GetButtonUp()->setTouchEnabled(true);
	Buttons::GetIntance()->GetButtonTips()->setTouchEnabled(true);
}

void Buttons::SetTouchDisable()
{
	Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(false);
	Buttons::GetIntance()->GetButtonDown()->setTouchEnabled(false);
	Buttons::GetIntance()->GetButtonLeft()->setTouchEnabled(false);
	Buttons::GetIntance()->GetButtonRight()->setTouchEnabled(false);
	Buttons::GetIntance()->GetButtonUp()->setTouchEnabled(false);
	Buttons::GetIntance()->GetButtonTips()->setTouchEnabled(false);
}
