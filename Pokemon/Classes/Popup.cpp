#include "ui\UITabControl.h"
#include "Popup.h"
#include "ResourceManager.h"
#include "Bag.h"
#include "Pokemon\Charizard.h"
#include "Pokemon\Charmeleon.h"
#include "Pokemon\Chikorita.h"
#include "Pokemon\Squirtle.h"
#include "Scene\BattleScene.h"
#include "Pokemon.h"
#include "Buttons.h"
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
    const char *GAME_FONT = "res/UI/Label/MarkerFelt.ttf";
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
		//this->setUpTouches();


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
			this->runAction(Sequence::create(FadeTo::create(ANIMATION_TIME, 0), RemoveSelf::create(false), NULL));
		}
		else {
			this->removeFromParentAndCleanup(false);
		}
	}

	void PopupDelegates::setUpTouches()
	{

		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [=](Touch* touch, Event* event) {
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
			node->addChild(layoutsetting, 3);
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
//			auto tab = TabControl::create();
//			tab->setContentSize(Size(300, 100));
//			tab->setHeaderHeight(20);
//			tab->setHeaderWidth(100);
//			tab->setHeaderDockPlace(TabControl::Dock::TOP);
//			tab->setPosition(winSize / 2);
//			node->addChild(tab, 101);
//			auto headerMP = TabHeader::create();
//			headerMP->setTitleText("My Pokemon");
//			headerMP->setTitleColor(Color4B(0, 0, 0, 255));
//			headerMP->loadTextureBackGround("res/Background/2.png");
//			headerMP->setTitleFontName(FONT::GAME_FONT);
//
//			auto headerPO = TabHeader::create();
//			headerPO->loadTextureBackGround("res/Background/2.png");
//			headerPO->setTitleText("Box Pokemon");
//			headerPO->setTitleColor(Color4B(0, 0, 0, 255));
//			headerPO->setTitleFontName(FONT::GAME_FONT);
//
//			auto headerMI = TabHeader::create();
//			headerMI->loadTextureBackGround("res/Background/2.png");
//			headerMI->setTitleText("My Item");
//			headerMI->setTitleColor(Color4B(0, 0, 0, 255));
//			headerMI->setTitleFontName(FONT::GAME_FONT);
//
//			auto containerMP = Layout::create();
//#pragma region Tab1
//			auto listView = ui::ListView::create();
//			//listView->setTouchEnabled(false);
//			listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
//			listView->setAnchorPoint(Vec2(0.5, 0.5));
//			listView->setContentSize(Size(280, 140));
//			listView->setScale(0.8);
//			listView->setPosition(Vec2(tab->getContentSize().width / 2, 0));
//			listView->setClippingEnabled(true);
//			containerMP->addChild(listView,204);
//			listView->addEventListener((ListView::ccListViewCallback)CC_CALLBACK_2(Popup::SelectedItemEvent, node));
//			
//			auto list = Bag::GetInstance()->GetListPokemon();
//			auto sizeOfPokemon = list.size();
//			for (int i = 0; i < 6; i++)
//			{
//				ui::Button *button = ResourceManager::GetInstance()->GetButtonById(12);
//				button->setTag(i);
//				if (list.at(i) != nullptr)
//				{
//					string name = list.at(i)->GetName();
//					string level = "Level:" + to_string(list.at(i)->GetLevel());
//					auto sprite = list.at(i)->GetSpriteFront();
//					sprite->removeFromParentAndCleanup(false);
//					sprite->setScale(1);
//					sprite->setTag(i);
//					sprite->setPosition(button->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
//						button->getPosition().y + listView->getContentSize().height / 3);
//					Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
//					labelName->setString(name);
//					labelName->setColor(Color3B(0, 0, 0));
//					labelName->setPosition(button->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
//						button->getPosition().y + listView->getContentSize().height * 4 / 5);
//					Label* labelLv = ResourceManager::GetInstance()->GetLabelById(0);
//					labelLv->setString(level);
//					labelLv->setColor(Color3B(0, 0, 0));
//					labelLv->setPosition(button->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
//						button->getPosition().y + listView->getContentSize().height * 1 / 5);
//					listView->addChild(sprite, 202);
//					listView->addChild(labelName, 202);
//					listView->addChild(labelLv, 202);
//				}
//				listView->pushBackCustomItem(button);
//			}
//
//#pragma endregion
//			auto containerPO = Layout::create();
//#pragma region Tab2
//			auto listViewPO = ui::ListView::create();
//			listViewPO->setTouchEnabled(false);
//			listViewPO->setDirection(ui::ScrollView::Direction::HORIZONTAL);
//			listViewPO->setAnchorPoint(Vec2(0.5, 0.5));
//			listViewPO->setContentSize(Size(280, 140));
//			listViewPO->setScale(0.8);
//			CCLOG("%f", listViewPO->getContentSize().width);
//			listViewPO->setGlobalZOrder(200);
//			listViewPO->setPosition(Vec2(tab->getContentSize().width / 2, 0));
//			listViewPO->setClippingEnabled(true);
//			containerPO->addChild(listViewPO);
//			int sizeOfPokemonOver = Bag::GetInstance()->GetListPokemonOver().size();
//			auto listOver = Bag::GetInstance()->GetListPokemonOver();
//			for (int i = 0; i < 10; i++)
//			{
//				ui::Button *buttonOver = ResourceManager::GetInstance()->GetButtonById(12);
//				buttonOver->setTag(i);
//				if (i < sizeOfPokemonOver)
//				{
//					string name = listOver.at(i)->GetName();
//					string level = "Level:" + to_string(list.at(i)->GetLevel());
//					auto sprite = listOver.at(i)->GetSpriteFront();
//					sprite->removeFromParentAndCleanup(false);
//					sprite->setScale(1);
//					sprite->setTag(i);
//					sprite->setPosition(buttonOver->getPosition().x + listViewPO->getContentSize().width* (i * 2 + 1) / 4,
//						buttonOver->getPosition().y + listViewPO->getContentSize().height / 2);
//					Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
//					labelName->setString(name);
//					labelName->setColor(Color3B(0, 0, 0));
//					labelName->setPosition(buttonOver->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
//						buttonOver->getPosition().y + listView->getContentSize().height * 4 / 5);
//					Label* labelLv = ResourceManager::GetInstance()->GetLabelById(0);
//					labelLv->setString(level);
//					labelLv->setColor(Color3B(0, 0, 0));
//					labelLv->setPosition(buttonOver->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
//						buttonOver->getPosition().y + listView->getContentSize().height * 1 / 5);
//					listViewPO->addChild(labelName, 202);
//					listViewPO->addChild(labelLv, 202);
//					listViewPO->addChild(sprite, 202);
//				}
//				listViewPO->pushBackCustomItem(buttonOver);
//			}
//#pragma endregion
//			auto containerMI = Layout::create();
//#pragma region Tab3
//			auto listViewMI = ui::ListView::create();
//			listViewMI->setTouchEnabled(false);
//			listViewMI->setDirection(ui::ScrollView::Direction::HORIZONTAL);
//			listViewMI->setAnchorPoint(Vec2(0.5, 0.5));
//			listViewMI->setContentSize(Size(280, 140));
//			listViewMI->setScale(0.8);
//			listViewMI->setGlobalZOrder(200);
//			listViewMI->setPosition(Vec2(tab->getContentSize().width / 2, 0));
//			listViewMI->setClippingEnabled(true);
//			containerMI->addChild(listViewMI);
//			int sizeOfItem = Bag::GetInstance()->GetListItem().size();
//			auto listItem = Bag::GetInstance()->GetListItem();
//			for (int i = 0; i < sizeOfItem; i++)
//			{
//				ui::Button *buttonItem = ResourceManager::GetInstance()->GetButtonById(12);
//				buttonItem->setTag(i);
//				string id = to_string(listItem.at(i)->GetId());
//				string name = listItem.at(i)->GetName();
//				string amount = "x" + to_string(listItem.at(i)->GetNumber());
//				auto sprite = listItem.at(i)->GetSpriteFront();
//				sprite->removeFromParentAndCleanup(false);
//				sprite->setTag(i);
//				sprite->setScale(2.5);
//				sprite->setPosition(buttonItem->getPosition().x + listViewMI->getContentSize().width* (i * 2 + 1) / 4,
//					buttonItem->getPosition().y + listViewMI->getContentSize().height / 2);
//				Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
//				labelName->setString(name);
//				labelName->setColor(Color3B(0, 0, 0));
//				labelName->setPosition(buttonItem->getPosition().x + listViewMI->getContentSize().width* (i * 2 + 1) / 4,
//					buttonItem->getPosition().y + listViewMI->getContentSize().height * 4 / 5);
//				Label* labelNumber = ResourceManager::GetInstance()->GetLabelById(0);
//				labelNumber->setString(amount);
//				labelNumber->setColor(Color3B(0, 0, 0));
//				labelNumber->setPosition(buttonItem->getPosition().x + listViewMI->getContentSize().width* (i * 2 + 1) / 4,
//					buttonItem->getPosition().y + listViewMI->getContentSize().height * 1 / 5);
//				listViewMI->addChild(labelName, 202);
//				listViewMI->addChild(labelNumber, 202);
//				listViewMI->addChild(sprite, 202);
//				listViewMI->pushBackCustomItem(buttonItem);
//			}
//#pragma endregion
//			tab->insertTab(0, headerMP, containerMP);
//			tab->insertTab(1, headerPO, containerPO);
//			tab->insertTab(2, headerMI, containerMI);
//			tab->setSelectTab(0);
//			CC_SAFE_RETAIN(tab);
//			CC_SAFE_RETAIN(headerMP);
//			CC_SAFE_RETAIN(headerPO);
//			CC_SAFE_RETAIN(headerMI);
//

			Button *buttonYP = ResourceManager::GetInstance()->GetButtonById(13);
			buttonYP->setPosition(Vec2(winSize.width / 2 - buttonYP->getContentSize().width/1.2, winSize.height * 5 / 8));
			node->addChild(buttonYP,2);
			buttonYP->setScale(0.75);
			Button *buttonPO = ResourceManager::GetInstance()->GetButtonById(14);
			buttonPO->setScale(0.75);
			buttonPO->setPosition(Vec2(winSize.width / 2, winSize.height * 5 / 8));
			node->addChild(buttonPO, 2);

			Button *buttonYI = ResourceManager::GetInstance()->GetButtonById(15);
			buttonYI->setScale(0.75);
			buttonYI->setPosition(Vec2(winSize.width / 2 + buttonYP->getContentSize().width / 1.2, winSize.height * 5 / 8));
			node->addChild(buttonYI, 2);
			MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
				node->dismiss(true);
				Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
			});
			Menu *menu = Menu::create(noButton, NULL);
			node->addChild(menu, 2);
			menu->setPosition(winSize.width / 2, winSize.height / 2 - 150);
			menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

#pragma region Button Your Pokemon
			auto listView = ui::ListView::create();
			listView->setAnchorPoint(Vec2(0.5, 1));
			listView->setScale(0.8);
			listView->setDirection(ui::ScrollView::Direction::HORIZONTAL);
			listView->setAnchorPoint(Vec2(0.5, 0.5));
			listView->setContentSize(Size(280, 140));
			listView->setPosition(Vec2(winSize.width/2,winSize.height / 2.7));
			listView->setClippingEnabled(true);
			node->addChild(listView,2);						
			auto list = Bag::GetInstance()->GetListPokemon();
			auto sizeOfPokemon = list.size();
			for (int i = 0; i < 6; i++)
			{
				ui::Button *button = ResourceManager::GetInstance()->GetButtonById(12);
				button->setTag(i);
				if (list.at(i) != nullptr)
				{
					string name = list.at(i)->GetName();
					string level = "Level: " + to_string(list.at(i)->GetLevel());
					auto sprite = list.at(i)->GetSpriteFront();
					sprite->removeFromParentAndCleanup(false);
					sprite->setScale(1);
					sprite->setTag(i);
					sprite->setPosition(button->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
						button->getPosition().y + listView->getContentSize().height / 3);
					Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
					labelName->setString(name);
					labelName->setColor(Color3B(0, 0, 0));
					labelName->setPosition(button->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
						button->getPosition().y + listView->getContentSize().height * 4 / 5);
					Label* labelLv = ResourceManager::GetInstance()->GetLabelById(0);
					labelLv->setString(level);
					labelLv->setColor(Color3B(0, 0, 0));
					labelLv->setPosition(button->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
						button->getPosition().y + listView->getContentSize().height * 1 / 5);
					listView->addChild(sprite, 202);
					listView->addChild(labelName, 202);
					listView->addChild(labelLv, 202);
				}
				else
				{
					button->setTouchEnabled(false);
				}
				listView->pushBackCustomItem(button);
				button->addTouchEventListener([button,node,menu,winSize,listView,buttonPO,buttonYI,buttonYP](Ref * ref, ui::Widget::TouchEventType type)
				{
					if (Bag::GetInstance()->GetListItem().at(button->getTag()) != nullptr)
					{
						if (type == ui::Widget::TouchEventType::ENDED)
						{
							listView->setVisible(false);
							buttonPO->setVisible(false);
							buttonYI->setVisible(false);
							buttonYP->setVisible(false);
							listView->setVisible(false);
							menu->setVisible(false);

							auto layout = Layout::create();
							layout->setAnchorPoint(Vec2(0.5, 0.5));
							layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2.6));
							layout->setContentSize(Size(350, 200));
							layout->setBackGroundImage(IMAGEPATH::BACKGROUND_IMAGE);
							layout->setBackGroundImageScale9Enabled(true);
							node->addChild(layout);

							MenuItemImage *noButton2 = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node,buttonYP, buttonYI, buttonPO, menu, listView, layout](Ref *sender)
							{
								buttonPO->setVisible(true);
								buttonYI->setVisible(true);
								buttonYP->setVisible(true);
								layout->setVisible(false);
								listView->setVisible(true);
								menu->setVisible(true);
								
							});
							Menu *menu2 = Menu::create(noButton2, NULL);
							layout->addChild(menu2, 2);
							menu2->setPosition(layout->getContentSize().width, layout->getContentSize().height);
							int i = listView->getCurSelectedIndex();
							auto pokemon = Bag::GetInstance()->GetListPokemon().at(i);
							string type;
							switch (pokemon->GetType())
							{
							case 1:
							{
								type = "Normal";
								break;
							}
							case 2:
							{
								type = "Fire";
								break;
							}
							case 3:
							{
								type = "Water";
								break;
							}
							case 4:
							{
								type = "Grass";
								break;
							}
							case 5:
							{
								type = "Electric";
								break;
							}
							case 6:
							{
								type = "Flying";
								break;
							}
							case 7:
							{
								type = "Dragon";
								break;
							}
							default:
								break;
							}
							Label *name = Label::createWithTTF(pokemon->GetName(), FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
							name->setPosition(Vec2(layout->getContentSize().width/2,layout->getContentSize().height*5/6));
							
							Label *labelType = Label::createWithTTF("Type: " + type, FONT::GAME_FONT, 20);							
							labelType->setAnchorPoint(Vec2(0,0.5));
							labelType->setColor(Color3B(0, 0, 0));
							labelType->setPosition(Vec2(layout->getContentSize().width / 5, layout->getContentSize().height * 2 / 3));
							
							Label *labelLevel = Label::createWithTTF("Level: " + to_string(pokemon->GetLevel()), FONT::GAME_FONT, 20);
							labelLevel->setColor(Color3B(0, 0, 0));
							labelLevel->setAnchorPoint(Vec2(0, 0.5));
							labelLevel->setPosition(Vec2(layout->getContentSize().width * 3 / 5, layout->getContentSize().height * 2 / 3));

							Label *labelAttack = Label::createWithTTF("Attack: " + to_string(pokemon->GetAtk()), FONT::GAME_FONT, 20);
							labelAttack->setColor(Color3B(0, 0, 0));
							labelAttack->setAnchorPoint(Vec2(0, 0.5));
							labelAttack->setPosition(Vec2(layout->getContentSize().width / 5, layout->getContentSize().height * 2 / 3 - 35));

							Label *labelDef = Label::createWithTTF("Defender: " + to_string(pokemon->GetDef()), FONT::GAME_FONT, 20);
							labelDef->setColor(Color3B(0, 0, 0));
							labelDef->setAnchorPoint(Vec2(0, 0.5));
							labelDef->setPosition(Vec2(layout->getContentSize().width *3 / 5, layout->getContentSize().height * 2 / 3 - 35));

							Label *labelSpeed = Label::createWithTTF("Speed: " + to_string(pokemon->GetAtkSpeed()), FONT::GAME_FONT, 20);
							labelSpeed->setColor(Color3B(0, 0, 0));
							labelSpeed->setAnchorPoint(Vec2(0, 0.5));
							labelSpeed->setPosition(Vec2(layout->getContentSize().width / 5, layout->getContentSize().height * 2 / 3 - 70));

							Label *labelHp = Label::createWithTTF("Hp: " + to_string(pokemon->GetCurrentHP())+"/"+ to_string(pokemon->GetMaxHP()), FONT::GAME_FONT, 20);
							labelHp->setColor(Color3B(0, 0, 0));
							labelHp->setAnchorPoint(Vec2(0, 0.5));
							labelHp->setPosition(Vec2(layout->getContentSize().width * 3 / 5, layout->getContentSize().height * 2 / 3 - 70));
							
							Button *buttonMove = ResourceManager::GetInstance()->GetButtonById(19);
							buttonMove->setPosition(Vec2(layout->getContentSize().width / 3 - 10, layout->getContentSize().height/6));
							buttonMove->addTouchEventListener([name,i,pokemon,layout, node, menu, winSize, listView, buttonPO, buttonYI, buttonYP](Ref * ref, ui::Widget::TouchEventType type)
							{
								if (type == ui::Widget::TouchEventType::ENDED)
								{
									if (Bag::GetInstance()->SizeOfListPokemon() > 1 && Bag::GetInstance()->SizeOfListPokemonOver() < 10)
									{
										Bag::GetInstance()->RemovePokemonFormMyListToListOver(pokemon, i);
										/*log("%d", Bag::GetInstance()->GetListPokemonOver().size());
										buttonPO->setVisible(true);
										buttonYI->setVisible(true);
										buttonYP->setVisible(true);
										listView->setVisible(true);
										menu->setVisible(true);
										layout->setVisible(false);*/
										Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
										node->setVisible(false);
									}
									else
									{
										name->setString("Can't move");
									}
								}				
							});
							Button *buttonRelease = ResourceManager::GetInstance()->GetButtonById(20);
							buttonRelease->setPosition(Vec2(layout->getContentSize().width *2/3 + 10, layout->getContentSize().height / 6));
							buttonRelease->addTouchEventListener([name,i, layout, node, menu, winSize, listView, buttonPO, buttonYI, buttonYP](Ref * ref, ui::Widget::TouchEventType type)
							{
								if (type == ui::Widget::TouchEventType::ENDED)
								{
									if (Bag::GetInstance()->SizeOfListPokemon() > 1)
									{
										Bag::GetInstance()->ReleasePokemon(i);
										Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
										node->setVisible(false);
									}
									else
									{
										name->setString("Can't release");
									}
								}
							});
							layout->addChild(buttonRelease);
							layout->addChild(buttonMove);
							layout->addChild(labelHp);
							layout->addChild(labelSpeed);
							layout->addChild(labelDef);
							layout->addChild(labelAttack);
							layout->addChild(labelLevel);
							layout->addChild(labelType);
							layout->addChild(name);
						}
					}
				});
			}
#pragma endregion
#pragma region Button Pokemon Over
			
			
			auto listViewPO = ui::ListView::create();
			listViewPO->setAnchorPoint(Vec2(0.5, 1));
			listViewPO->setScale(0.8);
			listViewPO->setVisible(false);
			listViewPO->setDirection(ui::ScrollView::Direction::HORIZONTAL);
			listViewPO->setAnchorPoint(Vec2(0.5, 0.5));
			listViewPO->setContentSize(Size(280, 140));
			listViewPO->setPosition(Vec2(winSize.width / 2, winSize.height / 2.7));
			listViewPO->setClippingEnabled(true);
			node->addChild(listViewPO,2);
			int sizeOfPokemonOver = Bag::GetInstance()->GetListPokemonOver().size();
			auto listOver = Bag::GetInstance()->GetListPokemonOver();
			for (int i = 0; i < 10; i++)
			{
				ui::Button *buttonOver = ResourceManager::GetInstance()->GetButtonById(12);
				buttonOver->setTag(i);
				if (listOver.size() != 0)
				{
					if (listOver.at(i) != nullptr)
					{
						string name = listOver.at(i)->GetName();
						string level = "Level:" + to_string(listOver.at(i)->GetLevel());
						auto sprite = listOver.at(i)->GetSpriteFront();
						sprite->removeFromParentAndCleanup(false);
						sprite->setScale(1);
						sprite->setTag(i);
						sprite->setPosition(buttonOver->getPosition().x + listViewPO->getContentSize().width* (i * 2 + 1) / 4,
							buttonOver->getContentSize().height / 3);
						Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
						labelName->setString(name);
						labelName->setColor(Color3B(0, 0, 0));
						labelName->setPosition(buttonOver->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
							buttonOver->getPosition().y + listView->getContentSize().height * 4 / 5);
						Label* labelLv = ResourceManager::GetInstance()->GetLabelById(0);
						labelLv->setString(level);
						labelLv->setColor(Color3B(0, 0, 0));
						labelLv->setPosition(buttonOver->getPosition().x + listView->getContentSize().width* (i * 2 + 1) / 4,
							buttonOver->getPosition().y + listView->getContentSize().height * 1 / 5);
						listViewPO->addChild(labelName, 202);
						listViewPO->addChild(labelLv, 202);
						listViewPO->addChild(sprite, 202);
					}
					else
					{
						buttonOver->setTouchEnabled(false);
					}
				}
				listViewPO->pushBackCustomItem(buttonOver);
				buttonOver->addTouchEventListener([buttonOver, node, menu, winSize, listViewPO, buttonPO, buttonYI, buttonYP](Ref * ref, ui::Widget::TouchEventType type)
				{
					if (Bag::GetInstance()->GetListItem().at(buttonOver->getTag()) != nullptr)
					{
						if (type == ui::Widget::TouchEventType::ENDED)
						{
							listViewPO->setVisible(false);
							buttonPO->setVisible(false);
							buttonYI->setVisible(false);
							buttonYP->setVisible(false);
							listViewPO->setVisible(false);
							menu->setVisible(false);

							auto layout = Layout::create();
							layout->setAnchorPoint(Vec2(0.5, 0.5));
							layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2.6));
							layout->setContentSize(Size(350, 200));
							layout->setBackGroundImage(IMAGEPATH::BACKGROUND_IMAGE);
							layout->setBackGroundImageScale9Enabled(true);
							node->addChild(layout);

							MenuItemImage *noButton2 = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [buttonYP, buttonYI, buttonPO, menu, listViewPO, layout](Ref *sender)
							{
								buttonPO->setVisible(true);
								buttonYI->setVisible(true);
								buttonYP->setVisible(true);
								layout->setVisible(false);
								listViewPO->setVisible(true);
								menu->setVisible(true);
							});
							Menu *menu2 = Menu::create(noButton2, NULL);
							layout->addChild(menu2, 2);
							menu2->setPosition(layout->getContentSize().width, layout->getContentSize().height);
							int i = listViewPO->getCurSelectedIndex();
							auto pokemon = Bag::GetInstance()->GetListPokemonOver().at(i);
							string type;
							switch (pokemon->GetType())
							{
							case 1:
							{
								type = "Normal";
								break;
							}
							case 2:
							{
								type = "Fire";
								break;
							}
							case 3:
							{
								type = "Water";
								break;
							}
							case 4:
							{
								type = "Grass";
								break;
							}
							case 5:
							{
								type = "Electric";
								break;
							}
							case 6:
							{
								type = "Flying";
								break;
							}
							case 7:
							{
								type = "Dragon";
								break;
							}
							default:
								break;
							}
							Label *name = Label::createWithTTF(pokemon->GetName(), FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
							name->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height * 5 / 6));

							Label *labelType = Label::createWithTTF("Type: " + type, FONT::GAME_FONT, 20);
							labelType->setAnchorPoint(Vec2(0, 0.5));
							labelType->setColor(Color3B(0, 0, 0));
							labelType->setPosition(Vec2(layout->getContentSize().width / 5, layout->getContentSize().height * 2 / 3));

							Label *labelLevel = Label::createWithTTF("Level: " + to_string(pokemon->GetLevel()), FONT::GAME_FONT, 20);
							labelLevel->setColor(Color3B(0, 0, 0));
							labelLevel->setAnchorPoint(Vec2(0, 0.5));
							labelLevel->setPosition(Vec2(layout->getContentSize().width * 3 / 5, layout->getContentSize().height * 2 / 3));

							Label *labelAttack = Label::createWithTTF("Attack: " + to_string(pokemon->GetAtk()), FONT::GAME_FONT, 20);
							labelAttack->setColor(Color3B(0, 0, 0));
							labelAttack->setAnchorPoint(Vec2(0, 0.5));
							labelAttack->setPosition(Vec2(layout->getContentSize().width / 5, layout->getContentSize().height * 2 / 3 - 35));

							Label *labelDef = Label::createWithTTF("Defender: " + to_string(pokemon->GetDef()), FONT::GAME_FONT, 20);
							labelDef->setColor(Color3B(0, 0, 0));
							labelDef->setAnchorPoint(Vec2(0, 0.5));
							labelDef->setPosition(Vec2(layout->getContentSize().width * 3 / 5, layout->getContentSize().height * 2 / 3 - 35));

							Label *labelSpeed = Label::createWithTTF("Speed: " + to_string(pokemon->GetAtkSpeed()), FONT::GAME_FONT, 20);
							labelSpeed->setColor(Color3B(0, 0, 0));
							labelSpeed->setAnchorPoint(Vec2(0, 0.5));
							labelSpeed->setPosition(Vec2(layout->getContentSize().width / 5, layout->getContentSize().height * 2 / 3 - 70));

							Label *labelHp = Label::createWithTTF("Hp: " + to_string(pokemon->GetCurrentHP()) + "/" + to_string(pokemon->GetMaxHP()), FONT::GAME_FONT, 20);
							labelHp->setColor(Color3B(0, 0, 0));
							labelHp->setAnchorPoint(Vec2(0, 0.5));
							labelHp->setPosition(Vec2(layout->getContentSize().width * 3 / 5, layout->getContentSize().height * 2 / 3 - 70));
							
							Button *buttonMove = ResourceManager::GetInstance()->GetButtonById(19);
							buttonMove->setPosition(Vec2(layout->getContentSize().width / 3 - 10, layout->getContentSize().height / 6));
							buttonMove->addTouchEventListener([name,i,pokemon,layout, node, menu, winSize, listViewPO, buttonPO, buttonYI, buttonYP](Ref * ref, ui::Widget::TouchEventType type)
							{
								if (type == ui::Widget::TouchEventType::ENDED)
								{
									if (Bag::GetInstance()->SizeOfListPokemon()<6)
									{
										Bag::GetInstance()->AddPokemonIntoMyList(pokemon, i);
										/*buttonPO->setVisible(true);
										buttonYI->setVisible(true);
										buttonYP->setVisible(true);
										listViewPO->setVisible(true);
										menu->setVisible(true);
										layout->setVisible(false);*/
										Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
										node->setVisible(false);
									}
									else
									{
										name->setString("Can't move");
									}
								}
							});
							
							Button *buttonRelease = ResourceManager::GetInstance()->GetButtonById(20);
							buttonRelease->setPosition(Vec2(layout->getContentSize().width * 2 / 3 + 10, layout->getContentSize().height / 6));
							buttonRelease->addTouchEventListener([name,i, pokemon, layout, node, menu, winSize, listViewPO, buttonPO, buttonYI, buttonYP](Ref * ref, ui::Widget::TouchEventType type)
							{
								if (type == ui::Widget::TouchEventType::ENDED)
								{
									if (Bag::GetInstance()->SizeOfListPokemonOver() > 1)
									{
										Bag::GetInstance()->ReleasePokemonOver(i);
										/*buttonPO->setVisible(true);
										buttonYI->setVisible(true);
										buttonYP->setVisible(true);
										listViewPO->setVisible(true);
										menu->setVisible(true);
										layout->setVisible(false);*/
										Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
										node->setVisible(false);
									}
									else
									{
										name->setString("Can't release");
									}
								}
							});

							layout->addChild(buttonMove);
							layout->addChild(buttonRelease);
							layout->addChild(labelHp);
							layout->addChild(labelSpeed);
							layout->addChild(labelDef);
							layout->addChild(labelAttack);
							layout->addChild(labelLevel);
							layout->addChild(labelType);
							layout->addChild(name);
						}
					}
				});
			}
#pragma endregion
#pragma region Buton Your Item
			
			auto listViewYI = ui::ListView::create();
			listViewYI->setAnchorPoint(Vec2(0.5, 1));
			listViewYI->setScale(0.8);
			listViewYI->setVisible(false);
			listViewYI->setDirection(ui::ScrollView::Direction::HORIZONTAL);
			listViewYI->setAnchorPoint(Vec2(0.5, 0.5));
			listViewYI->setContentSize(Size(280, 140));
			listViewYI->setPosition(Vec2(winSize.width / 2, winSize.height / 2.7));
			listViewYI->setClippingEnabled(true);
			node->addChild(listViewYI,2);
			int sizeOfItem = Bag::GetInstance()->GetListItem().size();
			auto listItem = Bag::GetInstance()->GetListItem();
			for (int i = 0; i < sizeOfItem; i++)
			{
				ui::Button *buttonItem = ResourceManager::GetInstance()->GetButtonById(12);
				buttonItem->setTag(i);
				string id = to_string(listItem.at(i)->GetId());
				string name = listItem.at(i)->GetName();
				string amount = "x" + to_string(listItem.at(i)->GetNumber());
				auto sprite = listItem.at(i)->GetSpriteFront();
				sprite->removeFromParentAndCleanup(false);
				sprite->setTag(i);
				sprite->setScale(2.5);
				sprite->setPosition(buttonItem->getPosition().x + listViewYI->getContentSize().width* (i * 2 + 1) / 4,
					buttonItem->getPosition().y + listViewYI->getContentSize().height / 2);
				Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
				labelName->setString(name);
				labelName->setColor(Color3B(0, 0, 0));
				labelName->setPosition(buttonItem->getPosition().x + listViewYI->getContentSize().width* (i * 2 + 1) / 4,
					buttonItem->getPosition().y + listViewYI->getContentSize().height * 4 / 5);
				Label* labelNumber = ResourceManager::GetInstance()->GetLabelById(0);
				labelNumber->setString(amount);
				labelNumber->setColor(Color3B(0, 0, 0));
				labelNumber->setPosition(buttonItem->getPosition().x + listViewYI->getContentSize().width* (i * 2 + 1) / 4,
					buttonItem->getPosition().y + listViewYI->getContentSize().height * 1 / 5);
				listViewYI->addChild(labelName, 202);
				listViewYI->addChild(labelNumber, 202);
				listViewYI->addChild(sprite, 202);
				listViewYI->pushBackCustomItem(buttonItem);
				buttonItem->addTouchEventListener([buttonItem, node, menu, winSize, listViewYI, buttonPO, buttonYI, buttonYP](Ref * ref, ui::Widget::TouchEventType type)
				{
					if (Bag::GetInstance()->GetListItem().at(buttonItem->getTag()) != nullptr)
					{
						if (type == ui::Widget::TouchEventType::ENDED)
						{
							listViewYI->setVisible(false);
							buttonPO->setVisible(false);
							buttonYI->setVisible(false);
							buttonYP->setVisible(false);
							listViewYI->setVisible(false);
							menu->setVisible(false);

							auto layout = Layout::create();
							layout->setAnchorPoint(Vec2(0.5, 0.5));
							layout->setPosition(Vec2(winSize.width / 2, winSize.height / 2.6));
							layout->setContentSize(Size(350, 200));
							layout->setBackGroundImage(IMAGEPATH::BACKGROUND_IMAGE);
							layout->setBackGroundImageScale9Enabled(true);
							node->addChild(layout);

							
							int i = listViewYI->getCurSelectedIndex();
							auto item = Bag::GetInstance()->GetListItem().at(i);
						
							Label *name = Label::createWithTTF(item->GetName(), FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
							name->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height * 5 / 6));

							Label *labeDescribe = Label::createWithTTF(item->GetDescribe(), FONT::GAME_FONT, 20);
							labeDescribe->setColor(Color3B(0, 0, 0));
							labeDescribe->setWidth(250);
							labeDescribe->setAnchorPoint(Vec2(0.5, 1));
							labeDescribe->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height * 2 / 3));
							labeDescribe->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);

							Label *alert = ResourceManager::GetInstance()->GetLabelById(0);
							alert->setColor(Color3B(0, 0, 0));
							alert->setWidth(250);
							alert->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 7));
							alert->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);


							Button* buttonUse = ResourceManager::GetInstance()->GetButtonById(21);
							buttonUse->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 5));
							buttonUse->setScaleX(0.7);
							buttonUse->addTouchEventListener([item,listViewYI,alert,buttonUse, name, layout, node, labeDescribe](Ref *ref, ui::Widget::TouchEventType type)
							{
								int curSelected = listViewYI->getCurSelectedIndex();
								if (curSelected == 0 || curSelected == 1 || curSelected == 2)
								{
									buttonUse->setVisible(false);
									labeDescribe->setVisible(false);
									auto newListPokemon = ui::ListView::create();
									newListPokemon->setAnchorPoint(Vec2(0.5, 1));
									newListPokemon->setScale(0.8);
									newListPokemon->setDirection(ui::ScrollView::Direction::HORIZONTAL);
									newListPokemon->setAnchorPoint(Vec2(0.5, 0.5));
									newListPokemon->setContentSize(Size(280, 140));
									newListPokemon->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2.2));
									newListPokemon->setClippingEnabled(true);
									layout->addChild(newListPokemon, 3);
									auto list = Bag::GetInstance()->GetListPokemon();
									for (int i = 0; i < 6; i++)
									{
										ui::Button *button = ResourceManager::GetInstance()->GetButtonById(12);
										button->setTag(i);
										Label* labelHealth = ResourceManager::GetInstance()->GetLabelById(0);
										labelHealth->setColor(Color3B(0, 0, 0));
										labelHealth->setPosition(button->getPosition().x + newListPokemon->getContentSize().width* (i * 2 + 1) / 4,
											button->getPosition().y + newListPokemon->getContentSize().height * 1 / 5);
										if (list.at(i) != nullptr)
										{
											string name = list.at(i)->GetName();
											string health;
											if (list.at(i)->IsAlive() == false)
											{
												health = "Fainted";
											}
											else
											{
												health = to_string(list.at(i)->GetCurrentHP()) + "/" + to_string(list.at(i)->GetMaxHP());
											}
											auto newsprite = list.at(i)->GetSpriteFront();
											newsprite->setScale(1);
											newsprite->setTag(i);
											newsprite->removeFromParent();
											newsprite->setPosition(button->getPosition().x + newListPokemon->getContentSize().width* (i * 2 + 1) / 4,
												button->getPosition().y + newListPokemon->getContentSize().height / 3);
											Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
											labelName->setString(name);
											labelName->setColor(Color3B(0, 0, 0));
											labelName->setPosition(button->getPosition().x + newListPokemon->getContentSize().width* (i * 2 + 1) / 4,
												button->getPosition().y + newListPokemon->getContentSize().height * 4 / 5);
											labelHealth->setString(health);

											newListPokemon->addChild(newsprite, 202);
											newListPokemon->addChild(labelName, 202);
											newListPokemon->addChild(labelHealth, 202);
										}
										else
										{
											button->setTouchEnabled(false);
										}
										newListPokemon->pushBackCustomItem(button);
										button->addTouchEventListener([labelHealth, item, listViewYI, alert, newListPokemon](Ref* ref, ui::Widget::TouchEventType type)
										{
											int index = listViewYI->getCurSelectedIndex();
											auto pokemon = Bag::GetInstance()->GetListPokemon().at(newListPokemon->getCurSelectedIndex());
											if (type == ui::Widget::TouchEventType::ENDED)
											{
												if (pokemon->GetCurrentHP() == pokemon->GetMaxHP())
												{
													alert->setString("Pokemon is full of HP");
												}
												else if (pokemon->IsAlive() == false)
												{
													alert->setString("Revive before heal");
												}
												else
												{
													if (item->GetNumber() < 1)
													{
														alert->setString("No enough item");
													}
													else
													{
														Bag::GetInstance()->HealthPokemon(index, pokemon);
														item->SetNumber(item->GetNumber() - 1);
														string health = to_string(pokemon->GetCurrentHP()) + "/" + to_string(pokemon->GetMaxHP());
														labelHealth->setString(health);
														alert->setString("Restores succes");
													}
												}
											}
										});
									}
								}							
								if (curSelected == 4 || curSelected == 5)
								{
									buttonUse->setVisible(false);
									labeDescribe->setVisible(false);
									auto newListPokemon = ui::ListView::create();
									newListPokemon->setAnchorPoint(Vec2(0.5, 1));
									newListPokemon->setScale(0.8);
									newListPokemon->setDirection(ui::ScrollView::Direction::HORIZONTAL);
									newListPokemon->setAnchorPoint(Vec2(0.5, 0.5));
									newListPokemon->setContentSize(Size(280, 140));
									newListPokemon->setPosition(Vec2(layout->getContentSize().width / 2, layout->getContentSize().height / 2.2));
									newListPokemon->setClippingEnabled(true);
									layout->addChild(newListPokemon, 3);
									auto list = Bag::GetInstance()->GetListPokemon();
									for (int i = 0; i < 6; i++)
									{
										ui::Button *button = ResourceManager::GetInstance()->GetButtonById(12);
										button->setTag(i);
										Label* labelHealth = ResourceManager::GetInstance()->GetLabelById(0);
										labelHealth->setColor(Color3B(0, 0, 0));
										labelHealth->setPosition(button->getPosition().x + newListPokemon->getContentSize().width* (i * 2 + 1) / 4,
											button->getPosition().y + newListPokemon->getContentSize().height * 1 / 5);
										if (list.at(i) != nullptr)
										{
											string name = list.at(i)->GetName();
											string health;
											if (list.at(i)->IsAlive() == false)
											{
												health = "Fainted";
											}
											else
											{
												health = to_string(list.at(i)->GetCurrentHP()) + "/" + to_string(list.at(i)->GetMaxHP());
											}
											auto newsprite = list.at(i)->GetSpriteFront();
											newsprite->setScale(1);
											newsprite->setTag(i);
											newsprite->removeFromParent();
											newsprite->setPosition(button->getPosition().x + newListPokemon->getContentSize().width* (i * 2 + 1) / 4,
												button->getPosition().y + newListPokemon->getContentSize().height / 3);
											Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
											labelName->setString(name);
											labelName->setColor(Color3B(0, 0, 0));
											labelName->setPosition(button->getPosition().x + newListPokemon->getContentSize().width* (i * 2 + 1) / 4,
												button->getPosition().y + newListPokemon->getContentSize().height * 4 / 5);
											labelHealth->setString(health);

											newListPokemon->addChild(newsprite, 202);
											newListPokemon->addChild(labelName, 202);
											newListPokemon->addChild(labelHealth, 202);
										}
										else
										{
											button->setTouchEnabled(false);
										}
										newListPokemon->pushBackCustomItem(button);
										button->addTouchEventListener([labelHealth, item, listViewYI, alert, newListPokemon](Ref* ref, ui::Widget::TouchEventType type)
										{
											int index = listViewYI->getCurSelectedIndex();
											auto pokemon = Bag::GetInstance()->GetListPokemon().at(newListPokemon->getCurSelectedIndex());
											if (type == ui::Widget::TouchEventType::ENDED)
											{
												if (pokemon->IsAlive() == true)
												{
													alert->setString("can't use");
												}
												else if (item->GetNumber() < 1)
												{
													alert->setString("No enough item");
												}																		
												else
												{
													Bag::GetInstance()->HealthPokemon(index, pokemon);
													item->SetNumber(item->GetNumber() - 1);
													string health = to_string(pokemon->GetCurrentHP()) + "/" + to_string(pokemon->GetMaxHP());
													labelHealth->setString(health);
													alert->setString("Revive succes");
												}
											}
										});
									}
								}
								if (curSelected == 6 || curSelected == 7 || curSelected == 8 || curSelected == 9)
								{
									labeDescribe->setString("You don't have this item");
								}
							});
							MenuItemImage *noButton2 = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node,labeDescribe,buttonYP, buttonYI, buttonPO, menu, listViewYI, layout](Ref *sender)
							{
								if (labeDescribe->isVisible() == true)
								{
									buttonPO->setVisible(true);
									buttonYI->setVisible(true);
									buttonYP->setVisible(true);
									layout->setVisible(false);
									listViewYI->setVisible(true);
									menu->setVisible(true);
								}
								else
								{
									node->setVisible(false);
									Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
								}
							});
							Menu *menu2 = Menu::create(noButton2, NULL);
							layout->addChild(menu2, 2);
							menu2->setPosition(layout->getContentSize().width, layout->getContentSize().height);
							layout->addChild(buttonUse);
							layout->addChild(labeDescribe);
							layout->addChild(name);
							layout->addChild(alert,100);

						}
					}
				});
			}
#pragma endregion
#pragma region Event Button 
			buttonYP->addTouchEventListener([listView, listViewPO, listViewYI](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					listView->setVisible(true);
					listViewPO->setVisible(false);
					listViewYI->setVisible(false);
				}
			});
			buttonPO->addTouchEventListener([listView, listViewPO, listViewYI](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					listView->setVisible(false);
					listViewPO->setVisible(true);
					listViewYI->setVisible(false);
				}
			});
			buttonYI->addTouchEventListener([listView, listViewPO, listViewYI](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					listView->setVisible(false);
					listViewPO->setVisible(false);
					listViewYI->setVisible(true);
				}
			});
			//listView->addEventListener((ListView::ccListViewCallback)CC_CALLBACK_2(Popup::SelectedItemEvent, node));
			
#pragma endregion
			CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 250);
			menu->removeFromParent();
			node->addChild(menu, 2);
			node->initBg(Size(300,100) + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}
	Popup * Popup::ChoosePokemon()
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{			
			Button *buttonCharmander = ResourceManager::GetInstance()->GetButtonById(12);
			buttonCharmander->setPosition(Vec2(winSize.width/2,winSize.height/2-buttonCharmander->getContentSize().height/4));
			node->addChild(buttonCharmander, 100);
			
			Button *buttonSquirtle = ResourceManager::GetInstance()->GetButtonById(12);
			buttonSquirtle->setPosition(Vec2(buttonCharmander->getPosition().x - buttonCharmander->getContentSize().width -10, buttonCharmander->getPosition().y));
			node->addChild(buttonSquirtle, 100);
			
			Button *buttonChikorita = ResourceManager::GetInstance()->GetButtonById(12);
			buttonChikorita->setPosition(Vec2(buttonCharmander->getPosition().x + buttonCharmander->getContentSize().width + 10, buttonCharmander->getPosition().y));
			node->addChild(buttonChikorita, 100);

			MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
				node->dismiss(true);
				Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
			});
			
			Pokemon *charmander = new Charmander();
			Sprite *spriteCharmander = charmander->GetSpriteFront();
			spriteCharmander->setScale(2);
			spriteCharmander->setAnchorPoint(Vec2(0.5, 0));
			spriteCharmander->setPosition(buttonCharmander->getContentSize().width/2, buttonCharmander->getContentSize().height / 4);
			buttonCharmander->addChild(spriteCharmander,102);
			string nameCharmander = "Charmander - Fire";
			Label *labelCharmander = ResourceManager::GetInstance()->GetLabelById(0);
			labelCharmander->setString(nameCharmander);
			labelCharmander->setColor(Color3B(0, 0, 0));
			labelCharmander->setPosition(buttonCharmander->getContentSize().width / 2, buttonCharmander->getContentSize().height *5/6);
			buttonCharmander->addChild(labelCharmander,102);
			
			Squirtle *squirtle = new Squirtle();
			Sprite *spriteSquirtle = squirtle->GetSpriteFront();
			spriteSquirtle->setScale(2);
			spriteSquirtle->setAnchorPoint(Vec2(0.5, 0));
			spriteSquirtle->setPosition(buttonCharmander->getContentSize().width / 2 , buttonCharmander->getContentSize().height / 4);
			buttonSquirtle->addChild(spriteSquirtle, 102);
			string nameSquirtle = "Squirtle - Water";
			Label *labelSquirtle = ResourceManager::GetInstance()->GetLabelById(0);
			labelSquirtle->setString(nameSquirtle);
			labelSquirtle->setColor(Color3B(0, 0, 0));
			labelSquirtle->setPosition(buttonCharmander->getContentSize().width / 2, buttonCharmander->getContentSize().height * 5 / 6);
			buttonSquirtle->addChild(labelSquirtle, 102);
			
			Chikorita *chikorita = new Chikorita();
			Sprite *spriteChikorita = chikorita->GetSpriteFront();
			spriteChikorita->setScale(2);
			spriteChikorita->setAnchorPoint(Vec2(0.5, 0));
			spriteChikorita->setPosition(buttonCharmander->getContentSize().width / 2, buttonCharmander->getContentSize().height / 4);
			buttonChikorita->addChild(spriteChikorita, 102);
			string nameChikorita = "Chikorita - Grass";
			Label *labelChikorita = ResourceManager::GetInstance()->GetLabelById(0);
			labelChikorita->setString(nameChikorita);
			labelChikorita->setColor(Color3B(0, 0, 0));
			labelChikorita->setPosition(buttonCharmander->getContentSize().width / 2, buttonCharmander->getContentSize().height * 5 / 6);
			buttonChikorita->addChild(labelChikorita, 102);
			
			Label *labelPokemon = ResourceManager::GetInstance()->GetLabelById(0);
			labelPokemon->setColor(Color3B(0, 0, 0));
			labelPokemon->setPosition(Vec2(winSize.width / 2, winSize.height * 5 / 8));
			node->addChild(labelPokemon, 100);
			
			buttonCharmander->addTouchEventListener([labelPokemon,buttonCharmander,buttonChikorita,buttonSquirtle, charmander, winSize,node](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					Bag::GetInstance()->AddPokemon(charmander);
					labelPokemon->setString("Congratulations. Charmander will be your partner");
					buttonCharmander->setTouchEnabled(false);
					buttonChikorita->setTouchEnabled(false);
					buttonSquirtle->setTouchEnabled(false);
				}
			});

			buttonChikorita->addTouchEventListener([labelPokemon, buttonCharmander, buttonChikorita, buttonSquirtle, chikorita, winSize, node](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					Bag::GetInstance()->AddPokemon(chikorita);
					labelPokemon->setString("Congratulations. Chikorita will be your partner");
					buttonCharmander->setTouchEnabled(false);
					buttonChikorita->setTouchEnabled(false);
					buttonSquirtle->setTouchEnabled(false);
				}
			});

			buttonSquirtle->addTouchEventListener([labelPokemon, buttonCharmander, buttonChikorita, buttonSquirtle, squirtle, winSize, node](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					Bag::GetInstance()->AddPokemon(squirtle);
					labelPokemon->setString("Congratulations. Squirtle will be your partner");
					buttonCharmander->setTouchEnabled(false);
					buttonChikorita->setTouchEnabled(false);
					buttonSquirtle->setTouchEnabled(false);
				}
			});
			Menu *menu = Menu::create(noButton, NULL);
			node->addChild(menu, 2);
			menu->setPosition(winSize.width / 2, winSize.height / 2 - buttonCharmander->getContentSize().height / 1.1);
			menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);
			CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 180);
			node->initBg(Size(buttonCharmander->getContentSize().width*3 + CONFIRM_DIALOGUE_SIZE_OFFSET.width,
				buttonCharmander->getContentSize().height + CONFIRM_DIALOGUE_SIZE_OFFSET.height), "Choose the starting pokemon");
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}
	Popup * Popup::CreateBagItemInBattle()
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			Button *buttonPotion = ResourceManager::GetInstance()->GetButtonById(12);
			buttonPotion->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - buttonPotion->getContentSize().height / 4));
			node->addChild(buttonPotion, 100);

			Button *buttonSuperPotion = ResourceManager::GetInstance()->GetButtonById(12);
			buttonSuperPotion->setPosition(Vec2(buttonPotion->getPosition().x - buttonPotion->getContentSize().width - 10, buttonPotion->getPosition().y));
			node->addChild(buttonSuperPotion, 100);

			Button *buttonMaxPotion = ResourceManager::GetInstance()->GetButtonById(12);
			buttonMaxPotion->setPosition(Vec2(buttonPotion->getPosition().x + buttonPotion->getContentSize().width + 10, buttonPotion->getPosition().y));
			node->addChild(buttonMaxPotion, 100);

			MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
				node->dismiss(true);
			});

			Sprite *spritePotion = ResourceManager::GetInstance()->GetSpriteById(137);
			spritePotion->setScale(3);
			spritePotion->setAnchorPoint(Vec2(0.5, 0));
			spritePotion->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height / 3);
			buttonPotion->addChild(spritePotion, 102);
			
			string namePotion = "Potion";
			Label *labelPotion = ResourceManager::GetInstance()->GetLabelById(0);
			labelPotion->setString(namePotion);
			labelPotion->setColor(Color3B(0, 0, 0));
			labelPotion->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height * 5 / 6);
			buttonPotion->addChild(labelPotion, 102);
			
			Label *labelPotion2 = ResourceManager::GetInstance()->GetLabelById(0);
			labelPotion2->setString("Restores 50 HP");
			labelPotion2->setColor(Color3B(0, 0, 0));
			labelPotion2->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height * 1 / 6);
			buttonPotion->addChild(labelPotion2, 102);

			
			Sprite *spriteSuperPotion = ResourceManager::GetInstance()->GetSpriteById(138);
			spriteSuperPotion->setScale(3);
			spriteSuperPotion->setAnchorPoint(Vec2(0.5, 0));
			spriteSuperPotion->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height / 3);
			buttonSuperPotion->addChild(spriteSuperPotion, 102);
			
			string supperPotion = "Super Potion";
			Label *labelSuperPotion = ResourceManager::GetInstance()->GetLabelById(0);
			labelSuperPotion->setString(supperPotion);
			labelSuperPotion->setColor(Color3B(0, 0, 0));
			labelSuperPotion->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height * 5 / 6);
			buttonSuperPotion->addChild(labelSuperPotion, 102);
			
			Label *labelSuperPotion2 = ResourceManager::GetInstance()->GetLabelById(0);
			labelSuperPotion2->setString("Restores 100 HP");
			labelSuperPotion2->setColor(Color3B(0, 0, 0));
			labelSuperPotion2->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height * 1 / 6);
			buttonSuperPotion->addChild(labelSuperPotion2, 102);

			
			Sprite *spriteMaxPotion = ResourceManager::GetInstance()->GetSpriteById(139);
			spriteMaxPotion->setScale(3);
			spriteMaxPotion->setAnchorPoint(Vec2(0.5, 0));
			spriteMaxPotion->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height / 3);
			buttonMaxPotion->addChild(spriteMaxPotion, 102);
			
			string nameChikorita = "Max Potion";
			Label *labelMaxPotion = ResourceManager::GetInstance()->GetLabelById(0);
			labelMaxPotion->setString(nameChikorita);
			labelMaxPotion->setColor(Color3B(0, 0, 0));
			labelMaxPotion->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height * 5 / 6);
			buttonMaxPotion->addChild(labelMaxPotion, 102);
			
			Label *labelMaxPotion2 = ResourceManager::GetInstance()->GetLabelById(0);
			labelMaxPotion2->setString("Fully restores HP");
			labelMaxPotion2->setColor(Color3B(0, 0, 0));
			labelMaxPotion2->setPosition(buttonPotion->getContentSize().width / 2, buttonPotion->getContentSize().height * 1 / 6);
			buttonMaxPotion->addChild(labelMaxPotion2, 102);

			
			buttonPotion->addTouchEventListener([node](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					auto scene = ((BattleScene*)(node->getParent()));
					auto item = ((Potion*)(Bag::GetInstance()->GetListItem().at(0)));
					if (scene->GetTrainerPokemon()->GetCurrentHP() < scene->GetTrainerPokemon()->GetMaxHP() && item->GetNumber() > 0)
					{
						scene->SetButtonVisible(false);
						item->ReviceHealthPokemon(scene->GetTrainerPokemon());
						scene->UseItem();
						node->dismiss(true);
					}
				}
			});

			buttonSuperPotion->addTouchEventListener([node](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					auto scene = ((BattleScene*)(node->getParent()));
					auto item = ((SuperPotion*)(Bag::GetInstance()->GetListItem().at(1)));
					if (scene->GetTrainerPokemon()->GetCurrentHP() < scene->GetTrainerPokemon()->GetMaxHP() && item->GetNumber() > 0)
					{
						scene->SetButtonVisible(false);
						item->ReviceHealthPokemon(scene->GetTrainerPokemon());
						scene->UseItem();
						node->dismiss(true);
					}
				}
			});

			buttonMaxPotion->addTouchEventListener([node](Ref* sender, Widget::TouchEventType type)
			{
				if (type == Widget::TouchEventType::ENDED)
				{
					auto scene = ((BattleScene*)(node->getParent()));
					auto item = ((MaxPotion*)(Bag::GetInstance()->GetListItem().at(2)));
					if (scene->GetTrainerPokemon()->GetCurrentHP() < scene->GetTrainerPokemon()->GetMaxHP() && item->GetNumber() > 0)
					{
						scene->SetButtonVisible(false);
						item->ReviceHealthPokemon(scene->GetTrainerPokemon());
						scene->UseItem();
						node->dismiss(true);
					}
				}
			});

			
			CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 180);
			node->initBg(Size(buttonPotion->getContentSize().width * 3 + CONFIRM_DIALOGUE_SIZE_OFFSET.width,
				buttonPotion->getContentSize().height + CONFIRM_DIALOGUE_SIZE_OFFSET.height), "Item Potion");
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}
	
	Popup * Popup::CreateBagInBattle()
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			auto listViewPokemon = ui::ListView::create();
			listViewPokemon->setDirection(ui::ScrollView::Direction::HORIZONTAL);
			listViewPokemon->setAnchorPoint(Vec2(0.5, 0.5));
			listViewPokemon->setContentSize(Size(280, 140));
			listViewPokemon->setScale(0.8);
			listViewPokemon->setPosition(Vec2(winSize.width/2,winSize.height/2-listViewPokemon->getContentSize().height/4));
			listViewPokemon->setClippingEnabled(true);
			MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
				if (((BattleScene*)(node->getParent()))->GetTrainerPokemon()->IsAlive())
				{
					auto list = Bag::GetInstance()->GetListPokemon();
					for (int i = 0; i < 6; i++)
					{
						if (list.at(i) != nullptr)
						{
							auto sprite = list.at(i)->GetSpriteFront();
							sprite->removeFromParentAndCleanup(false);
						}
					}
					node->dismiss(true);
				}
			});
			node->addChild(listViewPokemon, 200);
			int sizeofpokemon = Bag::GetInstance()->GetListPokemon().size();
			auto list = Bag::GetInstance()->GetListPokemon();
			for (int i = 0; i < 6; i++)
			{
				ui::Button *button = ResourceManager::GetInstance()->GetButtonById(12);
				button->setTag(i);
				if (list.at(i) != nullptr)
				{
					string name = list.at(i)->GetName();
					string percentHP = to_string(list.at(i)->GetCurrentHP() * 100 / list.at(i)->GetMaxHP());
					string level = "Level: " + to_string(list.at(i)->GetLevel());
					string hp = "HP: " + percentHP + "%";
					auto sprite = list.at(i)->GetSpriteFront();
					sprite->removeFromParentAndCleanup(false);
					sprite->setScale(1);
					sprite->setTag(i);
					sprite->setPosition(button->getPosition().x + listViewPokemon->getContentSize().width* (i * 2 + 1) / 4,
						button->getPosition().y + listViewPokemon->getContentSize().height / 3 + 10);
					Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
					labelName->setString(name);
					labelName->setColor(Color3B(0, 0, 0));
					labelName->setPosition(button->getPosition().x + listViewPokemon->getContentSize().width* (i * 2 + 1) / 4,
						button->getPosition().y + listViewPokemon->getContentSize().height * 4 / 5 + 10);
					Label* labelLv = ResourceManager::GetInstance()->GetLabelById(0);
					labelLv->setString(level);
					labelLv->setColor(Color3B(0, 0, 0));
					labelLv->setPosition(button->getPosition().x + listViewPokemon->getContentSize().width* (i * 2 + 1) / 4,
						button->getPosition().y + listViewPokemon->getContentSize().height * 1 / 5 + 15);
					Label* HP = ResourceManager::GetInstance()->GetLabelById(0);
					HP->setString(hp);
					HP->setColor(Color3B(0, 0, 0));
					HP->setPosition(button->getPosition().x + listViewPokemon->getContentSize().width* (i * 2 + 1) / 4,
						button->getPosition().y + listViewPokemon->getContentSize().height * 1 / 5 - 10);

					listViewPokemon->addChild(sprite, 202);
					listViewPokemon->addChild(labelName, 202);
					listViewPokemon->addChild(labelLv, 202);
					listViewPokemon->addChild(HP, 202);

					if (list.at(i)->IsAlive() == true)
					{
						button->addTouchEventListener([node, list](Ref* ref, Widget::TouchEventType type) {
							int tag = ((Button*)(ref))->getTag();
							switch (type)
							{
							case cocos2d::ui::Widget::TouchEventType::BEGAN:
								break;
							case cocos2d::ui::Widget::TouchEventType::MOVED:
								break;
							case cocos2d::ui::Widget::TouchEventType::ENDED:
								if (tag != 0)
								{
									if (((BattleScene*)(node->getParent()))->GetTrainerPokemon()->IsAlive())
									{
										Bag::GetInstance()->ChangePokemon(tag);
										((BattleScene*)(node->getParent()))->TrainerChangePokemon();
										((BattleScene*)(node->getParent()))->SetButtonVisible(false);
										for (int i = 0; i < 6; i++)
										{
											if (list.at(i) != nullptr)
											{
												auto sprite = list.at(i)->GetSpriteFront();
												sprite->removeFromParentAndCleanup(false);
											}
										}
										node->dismiss(true);
									}
									else
									{
										Bag::GetInstance()->ChangePokemon(tag);
										((BattleScene*)(node->getParent()))->TrainerChangePokemon();
										((BattleScene*)(node->getParent()))->StartBattle();
										for (int i = 0; i < 6; i++)
										{
											if (list.at(i) != nullptr)
											{
												auto sprite = list.at(i)->GetSpriteFront();
												sprite->removeFromParentAndCleanup(false);
											}
										}
										node->dismiss(true);
									}
								}
								break;
							case cocos2d::ui::Widget::TouchEventType::CANCELED:
								break;
							default:
								break;
							}
						});
					}
				}
				listViewPokemon->pushBackCustomItem(button);
			}
			Menu *menu = Menu::create(noButton, NULL);
			node->addChild(menu, 2);
			menu->setPosition(winSize.width / 2, winSize.height / 2 - listViewPokemon->getContentSize().height / 2 - 75);
			menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);
			CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 150);
			node->initBg(listViewPokemon->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, "Pokemon");
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}
	Popup * Popup::CreateShop()
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{
			auto listViewItemShop = ui::ListView::create();
			listViewItemShop->setDirection(ui::ScrollView::Direction::HORIZONTAL);
			listViewItemShop->setAnchorPoint(Vec2(0.5, 0.5));
			listViewItemShop->setContentSize(Size(280, 140));
			listViewItemShop->setScale(0.8);
			listViewItemShop->setPosition(Vec2(winSize.width / 2, winSize.height / 2 - listViewItemShop->getContentSize().height / 4));
			listViewItemShop->setClippingEnabled(true);
			node->addChild(listViewItemShop, 200);
			auto listItem = Bag::GetInstance()->GetListItem();
			MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
				node->dismiss(true);
				Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(true);
			});
			Menu *menu = Menu::create(noButton, NULL);
			node->addChild(menu, 2);
			menu->setPosition(winSize.width / 2, winSize.height / 2 - listViewItemShop->getContentSize().height / 1.2);
			menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);
			for (int i = 0; i < 10; i++)
			{
#pragma region Create UI
				ui::Button *buttonItem = ResourceManager::GetInstance()->GetButtonById(12);
				buttonItem->setTag(i);
				string id = to_string(listItem.at(i)->GetId());
				string name = listItem.at(i)->GetName();
				string price = "Price: " + to_string(listItem.at(i)->GetGold()) + " $";
				Sprite *sprite = ResourceManager::GetInstance()->GetSpriteById(137 + i);
				sprite->setTag(i);
				sprite->setScale(2.5);
				sprite->setPosition(buttonItem->getPosition().x + listViewItemShop->getContentSize().width* (i * 2 + 1) / 4,
					buttonItem->getPosition().y + listViewItemShop->getContentSize().height / 2);
				Label* labelName = ResourceManager::GetInstance()->GetLabelById(0);
				labelName->setString(name);
				labelName->setColor(Color3B(0, 0, 0));
				labelName->setPosition(buttonItem->getPosition().x + listViewItemShop->getContentSize().width* (i * 2 + 1) / 4,
					buttonItem->getPosition().y + listViewItemShop->getContentSize().height * 4 / 5);
				Label* labelNumber = ResourceManager::GetInstance()->GetLabelById(0);
				labelNumber->setString(price);
				labelNumber->setColor(Color3B(0, 0, 0));
				labelNumber->setPosition(buttonItem->getPosition().x + listViewItemShop->getContentSize().width* (i * 2 + 1) / 4,
					buttonItem->getPosition().y + listViewItemShop->getContentSize().height * 1 / 5);
				listViewItemShop->addChild(labelName, 202);
				listViewItemShop->addChild(labelNumber, 202);
				listViewItemShop->addChild(sprite, 202);
				listViewItemShop->pushBackCustomItem(buttonItem);
#pragma endregion
				buttonItem->addTouchEventListener([menu,winSize,node, listViewItemShop](Ref* ref, Widget::TouchEventType type)
				{
					if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
					{
						
						listViewItemShop->setVisible(false);
						auto layout = Layout::create();
						layout->setAnchorPoint(Vec2(0.5, 0.5));
						layout->setPosition(Vec2(winSize.width / 2,winSize.height/2.4));
						layout->setContentSize(Size(300, 150));
						layout->setBackGroundImage(IMAGEPATH::BACKGROUND_IMAGE);
						layout->setBackGroundImageScale9Enabled(true);
						node->addChild(layout);
						menu->setVisible(false);
						MenuItemImage *noButton2 = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [menu,listViewItemShop,layout](Ref *sender)
						{
							layout->setVisible(false);
							listViewItemShop->setVisible(true);
							menu->setVisible(true);
						});
						Menu *menu2 = Menu::create(noButton2, NULL);
						layout->addChild(menu2, 2);
						menu2->setPosition(layout->getContentSize().width, layout->getContentSize().height);
						int i = listViewItemShop->getCurSelectedIndex();
						auto listItem = Bag::GetInstance()->GetListItem().at(i);
						
						Sprite *spriteItem = listItem->GetSpriteFront();
						spriteItem->setScale(2.5);
						spriteItem->setPosition(Vec2(layout->getContentSize().width/4, layout->getPosition().y/2));
						spriteItem->removeFromParent();
						
						Label *labelName = ResourceManager::GetInstance()->GetLabelById(0);
						string name = listItem->GetName();
						labelName->setString(name);
						labelName->setColor(Color3B(0, 0, 0));
						labelName->setPosition(Vec2(layout->getContentSize().width / 4, layout->getPosition().y - 35));
						
						Label *labelPrice = ResourceManager::GetInstance()->GetLabelById(0);
						string price = "Price: "+to_string(listItem->GetGold())+" $";
						labelPrice->setString(price);
						labelPrice->setColor(Color3B(0, 0, 0));
						labelPrice->setPosition(Vec2(layout->getContentSize().width / 4, layout->getPosition().y / 4));
						
#pragma region Describe

						Label *labelDescribe = ResourceManager::GetInstance()->GetLabelById(0);
						//string describe = listItem->GetDescribe();
						switch (i)
						{
						case 0:
						{
							labelDescribe->setString("Restores 50 HP");
							break;
						}
						case 1:
						{
							labelDescribe->setString("Restores 100 HP");
							break;
						}
						case 2:
						{
							labelDescribe->setString("Fully restores HP");
							break;
						}
						case 3:
						{
							labelDescribe->setString("It fully restores the PP");
							break;
						}
						case 4:
						{
							labelDescribe->setString("Revive pokemon with half HP maximum");
							break;
						}
						case 5:
						{
							labelDescribe->setString("Revive pokemon with full HP");
							break;
						}
						case 6:
						{
							labelDescribe->setString("Evolution Fire Pokemon");
							break;
						}
						case 7:
						{
							labelDescribe->setString("Evolution Leaf Pokemon");
							break;
						}
						case 8:
						{
							labelDescribe->setString("Evolution Thunder Pokemon");
							break;
						}
						case 9:
						{
							labelDescribe->setString("Evolution Water Pokemon");
							break;
						}
						default:
							break;
						}
#pragma endregion
						labelDescribe->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
						labelDescribe->setWidth(140);
						labelDescribe->setAnchorPoint(Vec2(0.5, 1));
						labelDescribe->setColor(Color3B(0, 0, 0));
						labelDescribe->setPosition(Vec2(layout->getContentSize().width *3/4.3, layout->getPosition().y - 30));
						
						Label *labelNumber = ResourceManager::GetInstance()->GetLabelById(0);
						labelNumber->setString(to_string(1));
						labelNumber->setColor(Color3B(0, 0, 0));
						labelNumber->setPosition(Vec2(layout->getContentSize().width * 1.4 / 2, layout->getPosition().y / 2));

						Label *labelAlert = ResourceManager::GetInstance()->GetLabelById(0);
						string strGold = to_string(Bag::GetInstance()->GetGold());
						labelAlert->setString("Your gold: " + strGold + " $");
						labelAlert->setColor(Color3B(0, 0, 0));
						labelAlert->setPosition(Vec2(layout->getContentSize().width * 1.4 / 2, layout->getPosition().y / 7));

						auto buttonMinus = ResourceManager::GetInstance()->GetButtonById(16);
						buttonMinus->setPosition(Vec2(layout->getContentSize().width * 1.25 /2, layout->getPosition().y /2));
						buttonMinus->setScale(0.2);
						buttonMinus->addTouchEventListener([labelAlert,node, labelNumber](Ref* ref, Widget::TouchEventType type)
						{
							if (type == ui::Widget::TouchEventType::ENDED)
							{
								int num = stoi(labelNumber->getString());
								if (num != 1)
								{
									labelAlert->setString("Your gold: " + to_string(Bag::GetInstance()->GetGold()) + " $");
									num--;
									labelNumber->setString(to_string(num));
								}
							}
						});

						auto buttonAdd = ResourceManager::GetInstance()->GetButtonById(17);
						buttonAdd->setPosition(Vec2(layout->getContentSize().width * 3.3 / 4.3 , layout->getPosition().y / 2));
						buttonAdd->setScale(0.2);
						buttonAdd->addTouchEventListener([labelAlert,node, labelNumber](Ref* ref, Widget::TouchEventType type)
						{
							if (type == ui::Widget::TouchEventType::ENDED) 
							{
								int num = stoi(labelNumber->getString());
								if (num != 9)
								{
									labelAlert->setString("Your gold: " + to_string(Bag::GetInstance()->GetGold()) + " $");
									num++;
									labelNumber->setString(to_string(num));
								}
							}
						});
						
						auto buttonBuy = ResourceManager::GetInstance()->GetButtonById(18);
						buttonBuy->setPosition(Vec2(layout->getContentSize().width * 1.4 / 2, layout->getPosition().y / 3));
						buttonBuy->setScale(0.5);
						buttonBuy->addTouchEventListener([labelAlert,listItem,node, labelNumber](Ref* ref, Widget::TouchEventType type)
						{
							if (type == ui::Widget::TouchEventType::ENDED)
							{
								int num = stoi(labelNumber->getString());
								if (num* listItem->GetGold() <= Bag::GetInstance()->GetGold())
								{
									listItem->SetNumber(listItem->GetNumber() + num);
									labelNumber->setString("1");
									labelAlert->setString("Buy success");
									Bag::GetInstance()->SetGold(Bag::GetInstance()->GetGold() - num* listItem->GetGold());
								}
								else
								{
									labelAlert->setString("No enough money");
								}
							}
						});
			
						layout->addChild(labelAlert);
						layout->addChild(buttonBuy);
						layout->addChild(labelNumber);
						layout->addChild(buttonMinus);
						layout->addChild(buttonAdd);
						layout->addChild(labelName);
						layout->addChild(labelDescribe);
						layout->addChild(labelPrice);
						layout->addChild(spriteItem);
					}
				});
			}
			
			//listViewItemShop->addEventListener((ListView::ccListViewCallback)CC_CALLBACK_2(Popup::SelectedShopItemEvent,node));
			CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 150); 
			string str = "Shop item - Gold: " + to_string(Bag::GetInstance()->GetGold());
			node->initBg(listViewItemShop->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, "Shop item");
			node->autorelease();
			return node;
		}
		CC_SAFE_DELETE(node);
		return nullptr;
	}

	Popup *Popup::create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void()> &YesFunc)
	{
		Popup *node = new (std::nothrow)Popup();
		Size winSize = Director::getInstance()->getWinSize();
		if (node && node->init())
		{

			if (!lbl) {
				lbl = Label::createWithTTF(msg, FONT::GAME_FONT, 20);
				lbl->setWidth(300);
			}
			lbl->setPosition(winSize.width / 2, winSize.height / 2 - FONT::LABEL_OFFSET / 2);
			lbl->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
			lbl->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
			lbl->enableShadow(Color4B::BLACK, Size(0, -2));
			if (YesFunc) {
				MenuItemImage *yesButton = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref *sender) {

					YesFunc();
					node->dismiss(true);
				});

				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
				});


				Menu *menu = Menu::create(yesButton, noButton, NULL);
				node->addChild(menu, 2);
				menu->setPosition(winSize.width / 2, winSize.height / 2 - lbl->getContentSize().height / 2 - 75);
				menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

				lbl->setPosition(winSize / 2);
				CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 250);
			}
			else
			{
				MenuItemImage *noButton = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [node](Ref *sender) {
					node->dismiss(true);
					Buttons::GetIntance()->GetButtonTips()->setTouchEnabled(true);
				});
				Menu *menu = Menu::create(noButton, NULL);
				node->addChild(menu, 2);
				menu->setPosition(winSize.width / 2, winSize.height / 2 - lbl->getContentSize().height / 2 - 75);
				menu->alignItemsHorizontallyWithPadding(FONT::LABEL_OFFSET / 2);

				lbl->setPosition(winSize / 2);
				CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 250);
			}
			node->addChild(lbl, 3);
			node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
			node->autorelease();
			return node;
		}

		CC_SAFE_DELETE(node);
		return nullptr;
	}
	
	void Popup::initBg(Size size, const std::string &title)
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