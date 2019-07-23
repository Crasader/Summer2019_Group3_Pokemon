#include "Popup.h"
#include "ResourceManager.h"
#include "Bag.h"
USING_NS_CC;

using namespace ui;

namespace 
{
	cocos2d::Size CONFIRM_DIALOGUE_SIZE_OFFSET = Size(100, 150);
	const float ANIMATION_TIME = 0.15f;
	const float FADE_RATIO = 200;
}

namespace FONT 
{
	const float LABEL_OFFSET = 50;
	const float DESCRIPTION_TEXT_SIZE = 36;
	const float TITLE_TEXT_SIZE = 70;
	const char *GAME_FONT = "fonts/arial.ttf";
	const float LABEL_STROKE = 4;
}

namespace IMAGEPATH 
{
	const char *OK_BUTTON = "res/Button/ButtonExit.png";
	const char *OK_BUTTON_PRESSED = "res/Button/ButtonExit.png";
	const char *CANCEL_BUTTON = "res/Button/ButtonExit.png";
	const char *CANCEL_BUTTON_PRESSED = "res/Button/ButtonExit.png";
	const char *CLOSE_BUTTON = "res/Button/ButtonExit.png";
	const char *BACKGROUND_IMAGE_SHOP = "res/BackGround/shop.png";
}
namespace UICustom
{
	PopupDelegates *PopupDelegates::create()
	{
		PopupDelegates *node = new (std::nothrow)PopupDelegates();
		if (node && node->init())
		{
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}
	bool PopupDelegates::init()
	{
		Size winSize = Director::getInstance()->getWinSize();

		if (!LayerRadialGradient::initWithColor(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, FADE_RATIO), winSize.width / 1.7f, winSize / 2, 0.075f))
		{
			return false;
		}
		this->setOpacity(0);
		show(true);
		this->setUpTouches();
		return true;
	}
	void PopupDelegates::show(const bool animated)
	{
		if (animated)
		{
			this->runAction(FadeTo::create(ANIMATION_TIME, FADE_RATIO));
		}
		else
		{
			this->setOpacity(FADE_RATIO);
		}
	}
	void PopupDelegates::dismiss(const bool animated)
	{
		if (animated)
		{
			this->runAction(Sequence::create(FadeTo::create(ANIMATION_TIME, 0), RemoveSelf::create(), NULL));
		}
		else
		{
			this->removeFromParentAndCleanup(true);
		}
	}
	void PopupDelegates::setUpTouches()
	{

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [=](Touch* touch, Event* event)
		{
			if (_bg)
			{
				if (!_bg->getBoundingBox().containsPoint(this->convertToNodeSpace(touch->getLocation())))
				{
					this->dismiss(true);
				}
			}
			else
			{
				this->dismiss(true);
			}
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	Popup *Popup::createAbout()
	{
		Popup *node = new (std::nothrow)Popup();
		//node->setContentSize(Size(200, 200));
		node->setScale(0.5);
		//node->setScaleY(0.5);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (node && node->init())
		{
			auto label = Label::createWithTTF("About","fonts/arial.ttf",70);
			label->setPosition(Vec2(visibleSize.width/2,visibleSize.height*7/8));
			label->removeFromParent();
			node->addChild(label, 2);
			auto label2 = Label::createWithTTF("This game is created by TNVD team\n\n         Summer internship 2019", "fonts/arial.ttf", 40);
			label2->setPosition(Vec2(visibleSize.width / 2, visibleSize.height /2-30));
			label2->removeFromParent();
			node->addChild(label2, 2);
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}
	Popup * Popup::createSetting()
	{
		Popup *node = new (std::nothrow)Popup();
		node->setScale(0.4);
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (node && node->init())
		{
			auto label = Label::createWithTTF("Setting", "fonts/arial.ttf", 70);
			label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 7 / 8));
			label->removeFromParent();
			node->addChild(label, 2);
			auto labelSound = Label::createWithTTF("Sound:", "fonts/arial.ttf", 55);
			labelSound->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height / 2 - 100));
			labelSound->removeFromParent();
			node->addChild(labelSound, 2);
			auto labelMusic = Label::createWithTTF("Music:", "fonts/arial.ttf", 55);
			labelMusic->setPosition(Vec2(visibleSize.width / 2 - 80, visibleSize.height /2 ));
			labelMusic->removeFromParent();
			node->addChild(labelMusic, 2);
			auto checkboxMusic = ui::CheckBox::create("res/Checkbox/musicOff.png", "res/Checkbox/musicOn.png");
			checkboxMusic->setPosition(Vec2(visibleSize.width / 2 + 80, visibleSize.height / 2));
			node->addChild(checkboxMusic, 2);
			auto checkboxSound = ui::CheckBox::create("res/Checkbox/audioOff.png", "res/Checkbox/audioOn.png");
			checkboxSound->setPosition(Vec2(visibleSize.width / 2 + 80, visibleSize.height / 2 - 100));
			node->addChild(checkboxSound, 2);
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}
	Popup * Popup::createShop()
	{
		Popup *node = new (std::nothrow)Popup();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (node && node->init())
		{
			auto button = ResourceManager::GetInstance()->GetButtonById(8);
			button->setPosition(visibleSize / 2);
			button->removeFromParent();
			node->addChild(button,5);
			button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					/*Bag::GetInstance()->GetListItem().at(0)->SetNumber(Bag::GetInstance()->GetListItem().at(0)->GetNumber()+1);						
					int index = Bag::GetInstance()->GetListItem().at(0)->GetNumber();
					log("%d", index);*/					
				}
			});
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}
	void Popup::initBg(Size size)
	{
		//_bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE_SHOP);
		//this->addChild(_bg);
		//Size visibleSize = Director::getInstance()->getVisibleSize();
		//_bg->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
		////_bg->setScale9Enabled(true);
		//_bg->setContentSize(size);
	}
}
