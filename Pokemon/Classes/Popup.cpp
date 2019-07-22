

#include "Popup.h"
#include "..\..\..\Summer2019_Group3\Pokemon\Classes\Popup.h"

USING_NS_CC;

using namespace ui;

namespace  {
    cocos2d::Size CONFIRM_DIALOGUE_SIZE_OFFSET = Size(100,150);
    const float ANIMATION_TIME = 0.15f;
    const float FADE_RATIO = 150;
}

namespace FONT {
    const float LABEL_OFFSET = 50;
    const float DESCRIPTION_TEXT_SIZE = 20;
    const float TITLE_TEXT_SIZE = 30;
    const char *GAME_FONT = "fonts/Marker Felt.ttf";
    const float LABEL_STROKE = 4;
}

namespace IMAGEPATH {
    const char *OK_BUTTON = "res/UI/Button/Ok.png";
    const char *OK_BUTTON_PRESSED = "res/UI/Button/OkPressed.png";
    const char *CANCEL_BUTTON = "res/UI/Button/Cancel.png";
    const char *CANCEL_BUTTON_PRESSED = "res/UI/Button/CancelPressed.png";
    const char *CLOSE_BUTTON = "res/UI/Button/close.png";
    const char *BACKGROUND_IMAGE = "res/Background/popUpBase.png";
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
		if (animated) {
			this->runAction(FadeTo::create(ANIMATION_TIME, FADE_RATIO));
		}
		else {
			this->setOpacity(FADE_RATIO);
		}
	}
	void PopupDelegates::dismiss(const bool animated)
	{
		if (animated) {
			this->runAction(Sequence::create(FadeTo::create(ANIMATION_TIME, 0), RemoveSelf::create(), NULL));
		}
		else {
			this->removeFromParentAndCleanup(true);
		}
	}

	void PopupDelegates::setUpTouches()
	{

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
			if (_bg) {
				if (!_bg->getBoundingBox().containsPoint(this->convertToNodeSpace(touch->getLocation())))
				{
					this->dismiss(true);
				}
			}
			else {
				this->dismiss(true);
			}
			return true;
		};
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	Popup *Popup::createAsMessage(const std::string &title, const std::string &msg)
	{
		return createAsConfirmDialogue(title, msg, NULL);
	}

	Popup *Popup::createAsConfirmDialogue(const std::string &title, const std::string &msg, const std::function<void()> &YesFunc)
	{
		return create(title, msg, NULL, YesFunc);
	}
	Popup *Popup::createSetting(const std::string &title)
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{

			/*CheckBox *Sound = CheckBox::create(IMAGEPATH::SOUND_BUTTON, IMAGEPATH::SOUND_BUTTON_PRESSED, [=](Ref *sender) {
				node->dismiss(true);
			});
			CheckBox *Music = CheckBox::create(IMAGEPATH::MUSIC_BUTTON, IMAGEPATH::MUSIC_BUTTON_PRESSED, [=](Ref *sender) {
				node->dismiss(true);
			});
			Menu *menuSetting = Menu::create(Sound, Music, NULL);
			menuSetting->setPosition(winSize/2);
			menuSetting->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);*/
			MenuItemImage *yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref *sender) {
				node->dismiss(true);
			});

			MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
				node->dismiss(true);
			});


			Menu *menu = Menu::create(yesButton, noButton, NULL);
			node->addChild(menu, 2);
			menu->setPosition(winSize.width / 2, winSize.height / 2); // -menuSetting->getContentSize().height / 2 - 75);
			menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);
			CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 250);
			//node->addChild(menuSetting, 2);
			node->addChild(menu, 2);
			node->initBg(/*menuSetting->getContentSize() + */ CONFIRM_DIALOGUE_SIZE_OFFSET, title);
			node->autorelease();
			return node;
		}
	}
    Popup *Popup::create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void ()> &YesFunc)
    {
        Popup *node = new (std::nothrow)Popup();
        Size winSize = Director::getInstance()->getWinSize();
        if(node && node->init())
        {
            
            if(!lbl){
                lbl = Label::createWithTTF(msg, FONT::GAME_FONT,20);
				lbl->setWidth(300);
            }
            lbl->setPosition(winSize.width/2,winSize.height/2 - FONT::LABEL_OFFSET/2);
            lbl->enableOutline(Color4B::BLACK,FONT::LABEL_STROKE);
            lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
            lbl->enableShadow(Color4B::BLACK, Size(0, -2));

            
            if(YesFunc){
                MenuItemImage *yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON,IMAGEPATH::OK_BUTTON_PRESSED,[=](Ref *sender){
                    
                    YesFunc();
                    node->dismiss(true);
                });
                
                MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender){
                    node->dismiss(true);
                });
                
                
                Menu *menu = Menu::create(yesButton,noButton,NULL);
                node->addChild(menu,2);
                menu->setPosition(winSize.width/2, winSize.height/2 - lbl->getContentSize().height/2 - 75);
                menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET/2);
                
                lbl->setPosition(winSize/2);
                CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width,250);
            }
			else
			{
				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});
				Menu *menu = Menu::create(noButton, NULL);
				node->addChild(menu, 2);
				menu->setPosition(winSize.width / 2, winSize.height / 2 - lbl->getContentSize().height / 2 - 75);
				menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

				lbl->setPosition(winSize / 2);
				CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 250);
			}
            node->addChild(lbl,3);
            node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->autorelease();
            return node;
        }
        
        CC_SAFE_DELETE(node);
        return nullptr;
    }
    

    
    void Popup::initBg(Size size,const std::string &title)
    {
        
        Size winSize = Director::getInstance()->getWinSize();

        _bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE);
        this->addChild(_bg);
        
        _bg->setPosition(Point(winSize.width/2,winSize.height/2));
        _bg->setScale9Enabled(true);
        _bg->setContentSize(Size(size.width,size.height));
        
        ui::ImageView *fill = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE);
        _bg->addChild(fill);
        fill->setColor(Color3B(210,210,210));
        fill->setScale9Enabled(true);
        fill->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        fill->setPosition(Point(FONT::LABEL_OFFSET/4,FONT::LABEL_OFFSET/4));
        fill->setContentSize(Size(size.width - FONT::LABEL_OFFSET/2, size.height - FONT::LABEL_OFFSET* 2 ));
        
        
        Label *heading = Label::createWithTTF(title, FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
        heading->setPosition(_bg->getContentSize().width/2 , _bg->getContentSize().height - FONT::LABEL_OFFSET);
        _bg->addChild(heading);
        heading->enableOutline(Color4B::BLACK,FONT::LABEL_STROKE);
        heading->enableShadow(Color4B::BLACK, Size(0, -3));
    }
    
    
}

