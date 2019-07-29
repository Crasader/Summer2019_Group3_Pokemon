#include "BattleScene.h"
#include "Map\Town.h"
#include "Pokemon\Charmander.h"
#include "Pokemon\Chikorita.h"
#include "Pokemon\Squirtle.h"
#include "Pokemon\Pikachu.h"
#include "Pokemon\Garchomp.h"
#include "Pokemon\Pidgey.h"
#include "SimpleAudioEngine.h"
#define scale_hpBar 0.47

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
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("BattleScene.mp3", true);
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

void BattleScene::DamageStepWithPlayerAttackFirst(float deltaTime)
{
	if (this->m_opponent->IsAlive() && this->m_player->IsAlive())
	{
		if (this->m_statePlayer == true && this->m_stateOpponent == true)
		{
			Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
			this->m_stateBattleLog = false;
			this->m_statePlayer = false;
			this->m_stateOpponent = false;
			this->m_opponent->SetState(false);
			this->SetButtonVisible(true);
			this->m_labelBattleLog->setString("What will you do?");
			this->BattleLogSetOpacity(255);
			this->unschedule(schedule_selector(BattleScene::DamageStepWithPlayerAttackFirst));
		}
		else
		{
			if (this->m_stateBattleLog == true)
			{
				if (this->m_statePlayer == false)
				{
					Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
					this->m_stateBattleLog = false;
					this->m_player->Attack(this->m_opponent, this->playerSkill);
					this->schedule(schedule_selector(BattleScene::ReduceHpOpponent), 0.1);
				}
				else
				{
					Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
					this->m_stateBattleLog = false;
					this->m_opponent->Attack(this->m_player, this->oppSkill);
					this->schedule(schedule_selector(BattleScene::ReduceHpPlayer), 0.1);
				}
			}
			else
			{
				if (this->m_statePlayer == true && this->m_player->GetState() == true)
				{
					this->m_player->SetState(false);
					Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
					this->BattleLog(this->m_opponent->GetName() + " used " + this->oppSkill->GetName() + ".");
				}
			}
		}
	}
	else
	{
		this->EndBattle();
		this->unschedule(schedule_selector(BattleScene::DamageStepWithPlayerAttackFirst));
	}
}

void BattleScene::DamageStepWithOpponentAttackFirst(float deltaTime)
{
	if (this->m_player->IsAlive() && this->m_opponent->IsAlive())
	{
		if (this->m_statePlayer == true && this->m_stateOpponent == true)
		{
			Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
			this->m_stateBattleLog = false;
			this->m_statePlayer = false;
			this->m_stateOpponent = false;
			this->m_player->SetState(false);
			this->SetButtonVisible(true);
			this->m_labelBattleLog->setString("What will you do?");
			this->BattleLogSetOpacity(255);
			this->unschedule(schedule_selector(BattleScene::DamageStepWithOpponentAttackFirst));
		}
		else
		{
			if (this->m_stateBattleLog == true)
			{
				if (this->m_stateOpponent == false)
				{
					Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
					this->m_stateBattleLog = false;
					this->m_opponent->Attack(this->m_player, this->oppSkill);
					this->schedule(schedule_selector(BattleScene::ReduceHpPlayer), 0.1);
				}
				else
				{
					Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
					this->m_stateBattleLog = false;
					this->m_player->Attack(this->m_opponent, this->playerSkill);
					this->schedule(schedule_selector(BattleScene::ReduceHpOpponent), 0.1);
				}
			}
			else
			{
				if (this->m_stateOpponent == true && this->m_opponent->GetState() == true)
				{
					this->m_opponent->SetState(false);
					Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
					this->BattleLog(this->m_player->GetName() + " used " + this->playerSkill->GetName() + ".");
				}
			}
		}
	}
	else
	{
		this->EndBattle();
		this->unschedule(schedule_selector(BattleScene::DamageStepWithOpponentAttackFirst));
	}
}

void BattleScene::ReduceHpPlayer(float deltaTime)
{
	if (this->m_opponent->GetState() == true)
	{
		auto fadeOut = FadeOut::create(0.1);
		auto fadeIn = FadeIn::create(0.1);
		auto fadeOut_In = Sequence::create(fadeOut, fadeIn, fadeOut->clone(), fadeIn->clone(), nullptr);
		this->m_player->GetSpriteBack()->runAction(fadeOut_In);
		//
		//
		auto finished = CallFunc::create([this]() {
			this->m_stateOpponent = true;
		});
		if (this->m_player->GetCurrentHP() == 0)
		{
			auto sq = Sequence::create(ScaleTo::create(0.5, 0), finished, nullptr);
			this->m_hpPlayer->runAction(sq);
		}
		else
		{
			auto index = ((float)this->m_player->GetMaxHP() / this->m_player->GetCurrentHP());
			auto sq = Sequence::create(ScaleTo::create(0.5, scale_hpBar / index, this->m_hpPlayer->getScaleY()), finished, nullptr);
			this->m_hpPlayer->runAction(sq);
		}
		if (m_player->GetCurrentHP()*100/m_player->GetMaxHP()<20)
		{
			auto audio = SimpleAudioEngine::getInstance();
			audio->playEffect("LowHealth.mp3", true);
		}
		this->unschedule(schedule_selector(BattleScene::ReduceHpPlayer));
	}
}

void BattleScene::ReduceHpOpponent(float deltaTime)
{
	if (this->m_player->GetState() == true)
	{
		auto fadeOut = FadeOut::create(0.1);
		auto fadeIn = FadeIn::create(0.1);
		auto fadeOut_In = Sequence::create(fadeOut, fadeIn, fadeOut->clone(), fadeIn->clone(), nullptr);
		this->m_opponent->GetSpriteFront()->runAction(fadeOut_In);
		//
		//
		auto finished = CallFunc::create([this]() {
			this->m_statePlayer = true;
		});
		if (this->m_opponent->GetCurrentHP() == 0)
		{
			auto sq = Sequence::create(ScaleTo::create(0.5, 0), finished, nullptr);
			this->m_hpOpponent->runAction(sq);
		}
		else
		{
			auto index = ((float)this->m_opponent->GetMaxHP() / this->m_opponent->GetCurrentHP());
			auto sq = Sequence::create(ScaleTo::create(0.5, scale_hpBar / index, this->m_hpOpponent->getScaleY()), finished, nullptr);
			this->m_hpOpponent->runAction(sq);
		}
		this->unschedule(schedule_selector(BattleScene::ReduceHpOpponent));
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

	this->m_background = ResourceManager::GetInstance()->GetSpriteById(132);
	scale_x = visibleSize.width / this->m_background->getContentSize().width;
	scale_y = visibleSize.height / this->m_background->getContentSize().height;
	this->m_background->setScaleX(scale_x);
	this->m_background->setScaleY(scale_y);
	this->m_background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(this->m_background, -100);
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
	//
	//
	this->m_labelOppName = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelOppName->setString(this->m_opponent->GetName());
	this->m_labelOppName->setTextColor(Color4B::BLACK);
	this->m_labelOppName->setAnchorPoint(Vec2::ZERO);
	this->m_labelOppName->setScale(0.8);
	this->m_labelOppLevel = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelOppLevel->setString(to_string(this->m_opponent->GetLevel()));
	this->m_labelOppLevel->setTextColor(Color4B::BLACK);
	this->m_hpOpponent = ResourceManager::GetInstance()->GetSpriteById(131);
	this->m_hpOpponent->setAnchorPoint(Vec2::ZERO);
	this->m_hpOpponent->setScaleX(scale_hpBar);
	this->m_hpOpponent->setScaleY(0.12);
	auto obj = this->m_tiledmap->getObjectGroup("opponent");
	x = obj->getObject("name").at("x").asFloat();
	y = obj->getObject("name").at("y").asFloat();
	this->m_labelOppName->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_labelOppName, 0);
	x = obj->getObject("level").at("x").asFloat();
	y = obj->getObject("level").at("y").asFloat();
	this->m_labelOppLevel->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_labelOppLevel, 0);
	x = obj->getObject("hp").at("x").asFloat();
	y = obj->getObject("hp").at("y").asFloat();
	this->m_hpOpponent->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_hpOpponent, 0);
	//
	//
	this->m_labelPlayerName = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelPlayerName->setString(this->m_player->GetName());
	this->m_labelPlayerName->setTextColor(Color4B::BLACK);
	this->m_labelPlayerName->setAnchorPoint(Vec2::ZERO);
	this->m_labelPlayerName->setScale(0.8);
	this->m_labelPlayerLevel = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelPlayerLevel->setString(to_string(this->m_player->GetLevel()));
	this->m_labelPlayerLevel->setTextColor(Color4B::BLACK);
	this->m_hpPlayer = ResourceManager::GetInstance()->GetSpriteById(131);
	this->m_hpPlayer->setAnchorPoint(Vec2::ZERO);
	if (this->m_player->GetCurrentHP() == this->m_player->GetMaxHP())
	{
		this->m_hpPlayer->setScaleX(scale_hpBar);
	}
	else
	{
		auto index = ((float)this->m_player->GetMaxHP() / this->m_player->GetCurrentHP());
		this->m_hpPlayer->setScaleX(scale_hpBar / index);
	}
	this->m_hpPlayer->setScaleY(0.12);
	obj = this->m_tiledmap->getObjectGroup("player");
	x = obj->getObject("name").at("x").asFloat();
	y = obj->getObject("name").at("y").asFloat();
	this->m_labelPlayerName->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_labelPlayerName, 0);
	x = obj->getObject("level").at("x").asFloat();
	y = obj->getObject("level").at("y").asFloat();
	this->m_labelPlayerLevel->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_labelPlayerLevel, 0);
	x = obj->getObject("hp").at("x").asFloat();
	y = obj->getObject("hp").at("y").asFloat();
	this->m_hpPlayer->setPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_hpPlayer, 0);
}

void BattleScene::InitObject()
{
	int _random = rand() % 2 + 1;
	if (_random == 1)
	{
		this->m_player = new Pikachu();
		this->m_opponent = new Squirtle();
	}
	else
	{
		this->m_player = new Charmander();
		this->m_opponent = new Chikorita();
	}
	auto obj = this->m_tiledmap->getObjectGroup("pokemon");
	auto x = obj->getObject("player").at("x").asFloat();
	auto y = obj->getObject("player").at("y").asFloat();
	this->m_player->SetPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_player->GetSpriteBack(), 10);
	x = obj->getObject("opponent").at("x").asFloat();
	y = obj->getObject("opponent").at("y").asFloat();
	this->m_opponent->SetPosition(x * this->m_tiledmap->getScaleX(), y * this->m_tiledmap->getScaleY());
	this->addChild(this->m_opponent->GetSpriteFront(), 10);
	//
	//
	for (int i = 0; i < this->m_player->GetCountSkills(); i++)
	{
		this->addChild(this->m_player->GetSkillById(i)->GetSpriteFront(), 100);
		this->m_player->GetSkillById(i)->SetPosition(this->m_player->GetPosition());
	}
	for (int i = 0; i < this->m_opponent->GetCountSkills(); i++)
	{
		this->addChild(this->m_opponent->GetSkillById(i)->GetSpriteFront(), 100);
		this->m_opponent->GetSkillById(i)->SetPosition(this->m_opponent->GetPosition());
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
				this->m_labelSkill1->setString(this->m_player->GetSkillById(0) != nullptr ? this->m_player->GetSkillById(0)->GetName() : "-");
				this->m_labelSkill2->setString(this->m_player->GetSkillById(1) != nullptr ? this->m_player->GetSkillById(1)->GetName() : "-");
				this->m_labelSkill3->setString(this->m_player->GetSkillById(2) != nullptr ? this->m_player->GetSkillById(2)->GetName() : "-");
				this->m_labelSkill4->setString("Back");
			}
			else if (this->m_labelSkill1->getString() != "-")
			{
				int choice = ((Button*)sender)->getTag();
				this->SetButtonVisible(false);
				this->BattlePhase(choice);
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
				this->BattlePhase(choice);
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
				this->BattlePhase(choice);
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
			this->m_stateBattleLog = true;
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
		this->m_stateBattleLog = true;
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

void BattleScene::BattlePhase(int idSkill)
{
	if (this->m_player->GetAtkSpeed() >= this->m_opponent->GetAtkSpeed())
	{
		this->playerSkill = this->m_player->GetSkillById(idSkill);
		int id = rand() % this->m_opponent->GetCountSkills();
		this->oppSkill = this->m_opponent->GetSkillById(id);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
		this->BattleLog(this->m_player->GetName() + " used " + this->playerSkill->GetName() + ".");
		this->schedule(schedule_selector(BattleScene::DamageStepWithPlayerAttackFirst), 0.1);
	}
	else
	{
		int id = rand() % this->m_opponent->GetCountSkills();
		this->oppSkill = this->m_opponent->GetSkillById(id);
		this->playerSkill = this->m_player->GetSkillById(idSkill);
		Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
		this->BattleLog(this->m_opponent->GetName() + " used " + this->oppSkill->GetName() + ".");
		this->schedule(schedule_selector(BattleScene::DamageStepWithOpponentAttackFirst), 0.1);
	}
}

void BattleScene::EndBattle()
{
	this->m_stateBattleLog = false;
	Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
	auto listener = CallFunc::create([this]() {
		if (this->m_stateBattleLog == true)
		{
			Director::getInstance()->getRunningScene()->pause();
		}
	});
	auto rp = RepeatForever::create(Spawn::create(listener, nullptr));
	this->runAction(rp);
	if (this->m_player->IsAlive() == false)
	{
		this->BattleLog(this->m_player->GetName() + " fainted. You lose!");
	}
	else
	{
		this->BattleLog(this->m_opponent->GetName() + " fainted. You win!");
	}
}