#include "ui\UITabControl.h"
#include "Popup.h"
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
	const char *SOUND_BUTTON = "res/UI/Checkbox/1.png";
	const char *SOUND_BUTTON_CHECK = "res/UI/Checkbox/2.png";
	const char *MUSIC_BUTTON = "res/UI/Checkbox/3.png";
	const char *MUSIC_BUTTON_CHECK = "res/UI/Checkbox/4.png";
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
			Layout *layoutsetting = Layout::create();
			layoutsetting->setAnchorPoint(Vec2(0.5, 0.5));
			layoutsetting->setContentSize(Size(300, 100));
			layoutsetting->setPosition(winSize / 2);
			layoutsetting->removeFromParent();
			node->addChild(layoutsetting,3);
			CheckBox *checkboxSound = CheckBox::create(IMAGEPATH::SOUND_BUTTON, IMAGEPATH::SOUND_BUTTON_CHECK);
			checkboxSound->setPosition(Vec2(layoutsetting->getContentSize().width / 4, layoutsetting->getContentSize().height / 2));
			checkboxSound->setScale(2);
			CheckBox *checkboxMusic = CheckBox::create(IMAGEPATH::MUSIC_BUTTON, IMAGEPATH::MUSIC_BUTTON_CHECK);
			checkboxMusic->setPosition((Vec2(layoutsetting->getContentSize().width * 3 / 4, layoutsetting->getContentSize().height / 2)));
			checkboxMusic->setScale(2);
			layoutsetting->addChild(checkboxMusic, 5);
			layoutsetting->addChild(checkboxSound, 5);
			MenuItemImage *yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref *sender) {
				node->dismiss(true);
			});

			MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
				node->dismiss(true);
			});


			Menu *menu = Menu::create(yesButton, noButton, NULL);
			node->addChild(menu, 2);
			menu->setPosition(winSize.width / 2, winSize.height / 2 - layoutsetting->getContentSize().height / 2 - 75);
			menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);
			CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 250);
			//node->addChild(menuSetting, 2);
			menu->removeFromParent();
			node->addChild(menu, 2);
			node->initBg(layoutsetting->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
			node->autorelease();
			return node;
		}
	}
	Popup *Popup::createBag(const std::string &title)
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			auto tab = TabControl::create();
			tab->setContentSize(Size(300,100));
			tab->setHeaderHeight(20);
			tab->setHeaderWidth(100);
			tab->setHeaderDockPlace(TabControl::Dock::TOP);
			tab->setPosition(winSize / 2);
			node->addChild(tab, 101);
			auto headerMP = TabHeader::create();
			headerMP->setTitleText("My Pokemon");
			auto headerPO = TabHeader::create();
			headerPO->setTitleText("Pokemon Over");
			auto headerMI = TabHeader::create();
			headerMI->setTitleText("My Item");
			auto containerMP = Layout::create();
			containerMP->setOpacity(255);
			containerMP->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
			containerMP->setBackGroundColor(Color3B::GRAY);
			containerMP->setBackGroundColorOpacity(255);
			auto containerPO = Layout::create();
			containerPO->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
			containerPO->setOpacity(255);
			containerPO->setBackGroundColor(Color3B::BLUE);
			containerPO->setBackGroundColorOpacity(255);
			auto containerMI = Layout::create();
			containerMI->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
			containerMI->setOpacity(255);
			containerMI->setBackGroundColor(Color3B::RED);
			containerMI->setBackGroundColorOpacity(255);

			tab->insertTab(0, headerMP, containerMP);
			tab->insertTab(1, headerPO, containerPO);
			tab->insertTab(2, headerMI, containerMI);
			tab->setSelectTab(0);
			CC_SAFE_RETAIN(tab);
			CC_SAFE_RETAIN(headerMP);
			CC_SAFE_RETAIN(headerPO);
			CC_SAFE_RETAIN(headerMI);

			/*auto tab = TabControl::create();
			tab->setContentSize(Size(200.f, 200.f));
			tab->setHeaderHeight(20.f);
			tab->setHeaderWidth(70.f);
			tab->setHeaderSelectedZoom(.1f);
			tab->setHeaderDockPlace(TabControl::Dock::TOP);

			auto header1 = TabHeader::create();
			header1->setTitleText("background");
			header1->loadTextureBackGround("cocosui/check_box_normal_disable.png");
			auto header2 = TabHeader::create("cross", "cocosui/check_box_normal_disable.png", "cocosui/check_box_active.png");
			auto header3 = TabHeader::create("press&cross", "cocosui/check_box_normal.png",
				"cocosui/check_box_normal_press.png",
				"cocosui/check_box_active.png",
				"cocosui/check_box_normal_disable.png",
				"cocosui/check_box_active_disable.png");

			auto container1 = Layout::create();
			container1->setOpacity(255);
			container1->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
			container1->setBackGroundColor(Color3B::GRAY);
			container1->setBackGroundColorOpacity(255);
			auto container2 = Layout::create();
			container2->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
			container2->setOpacity(255);
			container2->setBackGroundColor(Color3B::BLUE);
			container2->setBackGroundColorOpacity(255);
			auto container3 = Layout::create();
			container3->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
			container3->setOpacity(255);
			container3->setBackGroundColor(Color3B::RED);
			container3->setBackGroundColorOpacity(255);

			tab->insertTab(0, header1, container1);
			tab->insertTab(1, header2, container2);
			tab->insertTab(2, header3, container3);

			tab->setSelectTab(2);
			CC_SAFE_RETAIN(tab);
			CC_SAFE_RETAIN(header1);
			CC_SAFE_RETAIN(header2);
			CC_SAFE_RETAIN(header3);
			node->addChild(tab,999);
			tab->setPosition(winSize / 2);*/

			MenuItemImage *yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref *sender) {
				node->dismiss(true);
			});

			MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
				node->dismiss(true);
			});


			Menu *menu = Menu::create(yesButton, noButton, NULL);
			node->addChild(menu, 2);
			menu->setPosition(winSize.width / 2, winSize.height / 2 - tab->getContentSize().height / 2 - 75);
			menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);
			CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 250);
			menu->removeFromParent();
			node->addChild(menu, 2);
			node->initBg(tab->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
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

