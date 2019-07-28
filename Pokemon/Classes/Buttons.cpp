#include "Buttons.h"
#include "ResourceManager.h"
#include "Popup.h"

Buttons* Buttons::m_button = NULL;
int Buttons::state = 0;

Buttons::Buttons()
{
	m_down = ResourceManager::GetInstance()->GetButtonById(1);//thay id khac
	m_up = ResourceManager::GetInstance()->GetButtonById(4);
	m_left = ResourceManager::GetInstance()->GetButtonById(2);
	m_right = ResourceManager::GetInstance()->GetButtonById(3);
	m_bag = ResourceManager::GetInstance()->GetButtonById(11);
	m_down->setPosition(Vec2(100, 70));
	m_up->setPosition(Vec2(100, 130));
	m_left->setPosition(Vec2(70, 100));
	m_right->setPosition(Vec2(130, 100));
	m_bag->setPosition(Vec2(500,100));
	m_down->setScale(0.4f);
	m_up->setScale(0.4f);
	m_left->setScale(0.4f);
	m_right->setScale(0.4f);
}

void Buttons::ButtonBagListener(Layer *layer, Camera* camera)
{
	m_bag->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			UICustom::Popup *popup = UICustom::Popup::createBagInBattle();
			popup->removeFromParent();
			popup->setAnchorPoint(Vec2(0.5, 0.5));
			popup->setPosition(camera->getPosition().x - popup->getContentSize().width / 2,
				camera->getPosition().y - popup->getContentSize().height / 2);
			layer->addChild(popup, 101);
		}
	});
}

void Buttons ::ButtonListener(Trainer *&mPlayer)
{
	m_up->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			mPlayer->WalkUp();
			state = 1;
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			mPlayer->StopWalkUp();
			state = 0;
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkup/1.png");
			break;
		}
		default:
		{
			mPlayer->StopWalkUp();
			state = 0;
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkup/1.png");
			break;
		}
		}
	});

	m_right->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			mPlayer->WalkRight();
			state = 2;
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			mPlayer->StopWalkRight();
			state = 0;
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkright/1.png");
			break;
		}
		default:
		{
			mPlayer->StopWalkRight();
			state = 0;
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkright/1.png");
			break;
		}
		}
	});

	m_left->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			mPlayer->WalkLeft();
			state = 3;
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			mPlayer->StopWalkLeft();
			state = 0;
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkleft/1.png");
			break;
		}
		default:
		{
			mPlayer->StopWalkLeft();
			state = 0;
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkleft/1.png");
			break;
		}
		}
	});

	m_down->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			mPlayer->WalkDown();
			state = 4;
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			mPlayer->StopWalkDown();
			state = 0;
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkdown/1.png");
			break;
		}
		default:
		{
			mPlayer->StopWalkDown();
			state = 0;
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkdown/1.png");
			break;
		}
		}
	});
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

Button * Buttons::GetButtonBag()
{
	return m_bag;
}

void Buttons::Remove()
{
	m_up->removeFromParentAndCleanup(true);
	m_down->removeFromParentAndCleanup(true);
	m_left->removeFromParentAndCleanup(true);
	m_right->removeFromParentAndCleanup(true);
	m_bag->removeFromParentAndCleanup(true);
	m_up->release();
	m_down->release();
	m_left->release();
	m_right->release();
	m_bag->release();
	m_down = ResourceManager::GetInstance()->GetButtonById(1);//thay id khac
	m_up = ResourceManager::GetInstance()->GetButtonById(4);
	m_left = ResourceManager::GetInstance()->GetButtonById(2);
	m_right = ResourceManager::GetInstance()->GetButtonById(3);
	m_bag = ResourceManager::GetInstance()->GetButtonById(11);
	m_down->setPosition(Vec2(100, 70));
	m_up->setPosition(Vec2(100, 130));
	m_left->setPosition(Vec2(70, 100));
	m_right->setPosition(Vec2(130, 100));
	m_bag->setPosition(Vec2(100, 600));
	m_down->setScale(0.4f);
	m_up->setScale(0.4f);
	m_left->setScale(0.4f);
	m_right->setScale(0.4f);
	//m_bag->setScale();
}

void Buttons:: UpdateButton(float x, float y) {
	m_left->setPosition(Vec2(x - 30, y));
	m_right->setPosition(Vec2(x + 30, y));
	m_up->setPosition(Vec2(x , y +30));
	m_down->setPosition(Vec2(x , y -30));
	m_bag->setPosition(Vec2(x + 400, y));
}