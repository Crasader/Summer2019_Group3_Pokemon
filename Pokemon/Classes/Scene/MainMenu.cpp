#include "Scene\MainMenu.h"
#include "ResourceManager.h"
#include "NPC\LakeNPC.h"
//#include "Scene\About.h"
#include "Popup.h"


using namespace cocos2d;
using namespace std;

Scene* MainMenu::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = ResourceManager::GetInstance()->GetSpriteById(101);
	backGround->removeFromParent();
	backGround->setAnchorPoint(Vec2(0, 0));
	backGround->setScale(visibleSize.width / backGround->getContentSize().width, visibleSize.height / backGround->getContentSize().height);
	addChild(backGround, -99);

	auto buttonPlay = ResourceManager::GetInstance()->GetButtonById(6);
	buttonPlay->removeFromParent();
	buttonPlay->setScale(0.2f);
	buttonPlay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 9));
	addChild(buttonPlay, -98);
	buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			/*UICustom::Popup *popup = UICustom::Popup::createShop();
			this->addChild(popup);*/
		}
	});

	auto buttonSetting = ResourceManager::GetInstance()->GetButtonById(8);
	buttonSetting->removeFromParent();
	buttonSetting->setScale(0.1f);
	buttonSetting->setPosition(Vec2(visibleSize.width / 20, visibleSize.height / 10));
	addChild(buttonSetting, -1);
	buttonSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				UICustom::Popup *popup = UICustom::Popup::createSetting();
				this->addChild(popup);
			}
		}
	});
	auto buttonAbout = ResourceManager::GetInstance()->GetButtonById(5);
	buttonAbout->removeFromParent();
	buttonAbout->setScale(0.25f);
	buttonAbout->setPosition(Vec2(visibleSize.width * 19 / 20, visibleSize.height / 10));
	addChild(buttonAbout, -1);
	buttonAbout->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			UICustom::Popup *popup = UICustom::Popup::createAbout();
			this->addChild(popup);
		}
	});


	auto buttonExit = ResourceManager::GetInstance()->GetButtonById(9);
	buttonExit->removeFromParent();
	buttonExit->setScale(0.1f);
	buttonExit->setPosition(Vec2(visibleSize.width * 19 / 20, visibleSize.height * 9 / 10));
	addChild(buttonExit, -1);
	buttonExit->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->end();
			exit(0);
		}
	});
	return true;
}