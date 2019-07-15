#include "BattleScene.h"
#include "Pokemon\Charmander.h"
#include "Pokemon\Chikorita.h"

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

cocos2d::Scene * BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create();
	scene->addChild(layer);
	return scene;
}

bool BattleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->InitTiledMap();

	this->InitObject();

	this->InitUI();

	this->AddEventListener();

	return true;
}

void BattleScene::update(float deltaTime)
{
}

void BattleScene::TypeWriter(float deltaTime)
{
	if (writing < this->m_labelBattleLog->getStringLength())
	{
		auto letter = this->m_labelBattleLog->getLetter(writing);
		if (letter != nullptr)
		{
			letter->setOpacity(255);
		}
		writing++;
	}
	else
	{
		writing = 0;
		this->m_labelBattleLog->setOpacity(255);
		this->unschedule(schedule_selector(BattleScene::TypeWriter));
	}
}

void BattleScene::BattleLogSetOpacity(GLubyte opacity)
{
	for (int i = 0; i < this->m_labelBattleLog->getStringLength(); i++)
	{
		auto letter = this->m_labelBattleLog->getLetter(i);
		if (letter != nullptr)
		{
			letter->setOpacity(opacity);
		}
	}
}

void BattleScene::InitTiledMap()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->m_tiledmap = ResourceManager::GetInstance()->GetTiledMapById(0);
	auto scale_x = visibleSize.width / this->m_tiledmap->getContentSize().width;
	auto scale_y = visibleSize.height / this->m_tiledmap->getContentSize().height;
	this->m_tiledmap->setScaleX(scale_x);
	this->m_tiledmap->setScaleY(scale_y);
	this->addChild(this->m_tiledmap, -10);
}

void BattleScene::InitUI()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->m_buttonFight = ResourceManager::GetInstance()->GetButtonById(5);
	this->m_buttonFight->setAnchorPoint(Vec2(1, 0.5));
	this->m_buttonFight->setPosition(Vec2(visibleSize.width, this->m_buttonFight->getContentSize().height * 4));
	this->m_buttonFight->setTag(0);

	this->m_buttonBag = ResourceManager::GetInstance()->GetButtonById(5);
	this->m_buttonBag->setAnchorPoint(Vec2(1, 0.5));
	this->m_buttonBag->setPosition(Vec2(visibleSize.width, this->m_buttonBag->getContentSize().height * 2.9));
	this->m_buttonBag->setTag(1);

	this->m_buttonPokemon = ResourceManager::GetInstance()->GetButtonById(5);
	this->m_buttonPokemon->setAnchorPoint(Vec2(1, 0.5));
	this->m_buttonPokemon->setPosition(Vec2(visibleSize.width, this->m_buttonPokemon->getContentSize().height * 1.8));
	this->m_buttonPokemon->setTag(2);

	this->m_buttonRun = ResourceManager::GetInstance()->GetButtonById(5);
	this->m_buttonRun->setAnchorPoint(Vec2(1, 0.5));
	this->m_buttonRun->setPosition(Vec2(visibleSize.width, this->m_buttonRun->getContentSize().height * 0.7));
	this->m_buttonRun->setTag(3);

	this->addChild(this->m_buttonFight, 0);
	this->addChild(this->m_buttonBag, 0);
	this->addChild(this->m_buttonPokemon, 0);
	this->addChild(this->m_buttonRun, 0);

	auto x = this->m_buttonFight->getContentSize().width / 2;
	auto y = this->m_buttonFight->getContentSize().height / 2;

	this->m_labelSkill1 = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelSkill1->setString("Fight");
	this->m_labelSkill1->setTag(0);
	this->m_labelSkill1->setPosition(x, y);

	this->m_labelSkill2 = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelSkill2->setString("Bag");
	this->m_labelSkill2->setTag(1);
	this->m_labelSkill2->setPosition(x, y);

	this->m_labelSkill3 = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelSkill3->setString("Pokemon");
	this->m_labelSkill3->setTag(2);
	this->m_labelSkill3->setPosition(x, y);

	this->m_labelSkill4 = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelSkill4->setString("Run");
	this->m_labelSkill4->setTag(3);
	this->m_labelSkill4->setPosition(x, y);

	this->m_labelOppHealth = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelOppHealth->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(this->m_labelOppHealth);
	this->m_labelOppHealth->setString(to_string(this->opponent->GetCurrentHP()) + "/" + to_string(this->opponent->GetMaxHP()));
	//
	//
	this->m_messageBox = ResourceManager::GetInstance()->GetSpriteById(130);
	auto scale_x = 0.7;
	auto scale_y = 0.7;
	this->m_messageBox->setScaleX(scale_x);
	this->m_messageBox->setScaleY(scale_y);
	this->m_messageBox->setPosition(visibleSize.width / 1.88, this->m_buttonFight->getContentSize().height * 2);
	this->addChild(this->m_messageBox, 0);
	this->m_labelBattleLog = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelBattleLog->setAnchorPoint(Vec2::ZERO);
	this->m_labelBattleLog->setScale(1.5);
	this->m_labelBattleLog->setTextColor(Color4B::BLACK);
	this->m_labelBattleLog->setString("What will you do?");
	this->m_labelBattleLog->setPosition(this->m_messageBox->getContentSize().width * scale_x / 10, this->m_messageBox->getContentSize().height * scale_y / 1.2);
	this->m_messageBox->addChild(this->m_labelBattleLog);
	//
	//
	this->m_buttonFight->addChild(this->m_labelSkill1);
	this->m_buttonBag->addChild(this->m_labelSkill2);
	this->m_buttonPokemon->addChild(this->m_labelSkill3);
	this->m_buttonRun->addChild(this->m_labelSkill4);

	this->m_oppName = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_oppName->setString(this->opponent->GetName());
	this->m_oppName->setTextColor(Color4B::BLACK);
	this->m_oppName->setAnchorPoint(Vec2::ZERO);
	this->m_oppName->setScale(0.8);
	this->m_oppLevel = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_oppLevel->setString(to_string(this->opponent->GetLevel()));
	this->m_oppLevel->setTextColor(Color4B::BLACK);
	auto obj = this->m_tiledmap->getObjectGroup("opponent");
	x = obj->getObject("name").at("x").asFloat();
	y = obj->getObject("name").at("y").asFloat();
	this->m_oppName->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_oppName, 0);
	x = obj->getObject("level").at("x").asFloat();
	y = obj->getObject("level").at("y").asFloat();
	this->m_oppLevel->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_oppLevel, 0);
	//
	//
	this->m_playerName = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_playerName->setString(this->player->GetName());
	this->m_playerName->setTextColor(Color4B::BLACK);
	this->m_playerName->setAnchorPoint(Vec2::ZERO);
	this->m_playerName->setScale(0.8);
	this->m_playerLevel = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_playerLevel->setString(to_string(this->player->GetLevel()));
	this->m_playerLevel->setTextColor(Color4B::BLACK);
	obj = this->m_tiledmap->getObjectGroup("player");
	x = obj->getObject("name").at("x").asFloat();
	y = obj->getObject("name").at("y").asFloat();
	this->m_playerName->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_playerName, 0);
	x = obj->getObject("level").at("x").asFloat();
	y = obj->getObject("level").at("y").asFloat();
	this->m_playerLevel->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_playerLevel, 0);
}

void BattleScene::InitObject()
{
	this->player = new Charmander();
	this->opponent = new Chikorita();
	auto obj = this->m_tiledmap->getObjectGroup("pokemon");
	auto x = obj->getObject("player").at("x").asFloat();
	auto y = obj->getObject("player").at("y").asFloat();
	player->GetSpriteBack()->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(player->GetSpriteBack(), 10);
	x = obj->getObject("opponent").at("x").asFloat();
	y = obj->getObject("opponent").at("y").asFloat();
	opponent->GetSpriteFront()->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(opponent->GetSpriteFront(), 10);
	//
	//
	for (int i = 0; i < player->GetCountSkills(); i++)
	{
		this->addChild(player->GetSkillById(i)->GetSpriteFront(), 100);
		player->GetSkillById(i)->GetSpriteFront()->setPosition(opponent->GetSpriteFront()->getPosition());
	}
	for (int i = 0; i < opponent->GetCountSkills(); i++)
	{
		this->addChild(opponent->GetSkillById(i)->GetSpriteFront(), 100);
		opponent->GetSkillById(i)->GetSpriteFront()->setPosition(player->GetSpriteBack()->getPosition());
	}
}

void BattleScene::AddEventListener()
{
	this->m_buttonFight->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			if (this->m_labelSkill1->getString() == "Fight")
			{
				this->m_labelSkill1->setString(this->player->GetSkillById(0) != nullptr ? this->player->GetSkillById(0)->GetName() : "-");
				this->m_labelSkill2->setString(this->player->GetSkillById(1) != nullptr ? this->player->GetSkillById(1)->GetName() : "-");
				this->m_labelSkill3->setString(this->player->GetSkillById(2) != nullptr ? this->player->GetSkillById(2)->GetName() : "-");
				this->m_labelSkill4->setString("Back");
			}
			else if (this->m_labelSkill1->getString() != "-")
			{
				int choice = ((Button*)sender)->getTag();
				this->SetButtonVisible(false);
				this->DamagePhase(choice);
			}
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->m_buttonBag->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			if (this->m_labelSkill2->getString() == "Bag")
			{
			}
			else if (this->m_labelSkill2->getString() != "-")
			{
				int choice = ((Button*)sender)->getTag();
				this->SetButtonVisible(false);
				this->DamagePhase(choice);
			}
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->m_buttonPokemon->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			if (this->m_labelSkill3->getString() == "Pokemon")
			{
			}
			else if (this->m_labelSkill3->getString() != "-")
			{
				int choice = ((Button*)sender)->getTag();
				this->SetButtonVisible(false);
				this->DamagePhase(choice);
			}
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
	this->m_buttonRun->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			if (this->m_labelSkill1->getString() == "Run")
			{
			}
			else
			{
				this->SetButtonVisible(true);
			}
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(BattleScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BattleScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
}

void BattleScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * e)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_Z:
		if (this->m_labelBattleLog->getOpacity() == 0)
		{
			this->unschedule(schedule_selector(BattleScene::TypeWriter));
			this->BattleLogSetOpacity(255);
			this->m_labelBattleLog->setOpacity(255);
		}
		else
		{
			this->m_state = true;
		}
	default:
		break;
	}
}

void BattleScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * e)
{
	switch (keyCode)
	{
	default:
		break;
	}
}

bool BattleScene::onTouchBegan(Touch * touch, Event * e)
{
	if (this->m_labelBattleLog->getOpacity() == 0)
	{
		this->unschedule(schedule_selector(BattleScene::TypeWriter));
		this->BattleLogSetOpacity(255);
		this->m_labelBattleLog->setOpacity(255);
	}
	else
	{
		this->m_state = true;
	}
	return true;
}

void BattleScene::BattleLog(string logg)
{
	this->m_labelBattleLog->setString(logg);
	this->BattleLogSetOpacity(0);
	this->m_labelBattleLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(BattleScene::TypeWriter), 0.1);
}

void BattleScene::SetButtonVisible(bool visible)
{
	this->m_labelSkill1->setString("Fight");
	this->m_labelSkill2->setString("Bag");
	this->m_labelSkill3->setString("Pokemon");
	this->m_labelSkill4->setString("Run");
	this->m_buttonFight->setVisible(visible);
	this->m_buttonBag->setVisible(visible);
	this->m_buttonPokemon->setVisible(visible);
	this->m_buttonRun->setVisible(visible);
}

void BattleScene::DamagePhase(int idSkill)
{
	if (this->player->GetAtkSpeed() >= this->opponent->GetAtkSpeed())
	{
		auto playerSkill = this->player->GetSkillById(idSkill);
		int id = rand() % this->opponent->GetCountSkills();
		auto oppSkill = this->opponent->GetSkillById(id);
		auto listener = CallFunc::create([this, playerSkill, oppSkill]() {
			this->m_labelOppHealth->setString(to_string(this->opponent->GetCurrentHP()) + "/" + to_string(this->opponent->GetMaxHP()));
			if (this->opponent->IsAlive())
			{
				if (this->player->GetState() == true && this->opponent->GetState() == true)
				{
					Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
					this->m_state = false;
					this->player->SetState(false);
					this->opponent->SetState(false);
					this->SetButtonVisible(true);
					this->m_labelBattleLog->setString("What will you do?");
					this->BattleLogSetOpacity(255);
					this->stopActionByTag(0);
				}
				else
				{
					if (this->m_state == true)
					{
						if (this->player->GetState() == false)
						{
							Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
							this->m_state = false;
							this->player->Attack(this->opponent, playerSkill);
						}
						else
						{
							Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
							this->m_state = false;
							this->opponent->Attack(this->player, oppSkill);
						}
					}
					else
					{
						if (this->player->GetState() == true)
						{
							string logg = this->player->GetName() + " used " + playerSkill->GetName();
							if (this->m_labelBattleLog->getString() == logg)
							{
								Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
								this->BattleLog(this->opponent->GetName() + " used " + oppSkill->GetName());
							}
						}
					}
				}
			}
			else
			{
				this->m_labelBattleLog->setString("");
				this->stopActionByTag(0);
			}
		});
		auto rp = RepeatForever::create(Spawn::create(listener, nullptr));
		rp->setTag(0);
		this->runAction(rp);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
		this->BattleLog(this->player->GetName() + " used " + playerSkill->GetName());
	}
	else
	{
		int id = rand() % this->opponent->GetCountSkills();
		auto oppSkill = this->opponent->GetSkillById(id);
		auto playerSkill = this->player->GetSkillById(idSkill);
		auto listener = CallFunc::create([this, playerSkill, oppSkill]() {
			if (this->player->IsAlive())
			{
				if (this->player->GetState() == true && this->opponent->GetState() == true)
				{
					this->m_labelOppHealth->setString(to_string(this->opponent->GetCurrentHP()) + "/" + to_string(this->opponent->GetMaxHP()));
					Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
					this->m_state = false;
					this->player->SetState(false);
					this->opponent->SetState(false);
					this->SetButtonVisible(true);
					this->m_labelBattleLog->setString("What will you do?");
					this->BattleLogSetOpacity(255);
					this->stopActionByTag(0);
				}
				else
				{
					if (this->m_state == true)
					{
						if (this->opponent->GetState() == false)
						{
							Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
							this->m_state = false;
							this->opponent->Attack(this->player, oppSkill);
						}
						else
						{
							Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
							this->m_state = false;
							this->player->Attack(this->opponent, playerSkill);
						}
					}
					else
					{
						if (this->opponent->GetState() == true)
						{
							string logg = this->opponent->GetName() + " used " + oppSkill->GetName();
							if (this->m_labelBattleLog->getString() == logg)
							{
								Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
								this->BattleLog(this->player->GetName() + " used " + playerSkill->GetName());
							}
						}
					}
				}
			}
			else
			{
				this->m_labelBattleLog->setString("");
				this->stopActionByTag(0);
			}
		});
		auto rp = RepeatForever::create(Spawn::create(listener, nullptr));
		rp->setTag(0);
		this->runAction(rp);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
		this->BattleLog(this->opponent->GetName() + " used " + oppSkill->GetName());
	}
}