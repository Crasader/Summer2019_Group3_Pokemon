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

	this->InitButton();

	this->scheduleUpdate();

	return true;
}

void BattleScene::update(float deltaTime)
{
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

void BattleScene::InitButton()
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
	//
	this->m_labelBattleLog = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelBattleLog->setPosition(visibleSize.width / 4, visibleSize.height / 4);
	this->m_labelOppHealth->setString(to_string(this->opponent->GetCurrentHP()) + "/" + to_string(this->opponent->GetMaxHP()));
	this->addChild(this->m_labelBattleLog);
	//
	this->m_buttonFight->addChild(this->m_labelSkill1);
	this->m_buttonBag->addChild(this->m_labelSkill2);
	this->m_buttonPokemon->addChild(this->m_labelSkill3);
	this->m_buttonRun->addChild(this->m_labelSkill4);

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
				this->m_buttonFight->setVisible(false);
				this->m_buttonBag->setVisible(false);
				this->m_buttonPokemon->setVisible(false);
				this->m_buttonRun->setVisible(false);
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
				this->m_labelSkill1->setString("Fight");
				this->m_labelSkill2->setString("Bag");
				this->m_labelSkill3->setString("Pokemon");
				this->m_labelSkill4->setString("Run");
			}
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			break;
		default:
			break;
		}
	});
}

void BattleScene::InitObject()
{
	this->player = new Charmander();
	this->opponent = new Chikorita();
	auto obj = this->m_tiledmap->getObjectGroup("pokemon");
	auto x = obj->getObject("player").at("x").asFloat();
	auto y = obj->getObject("player").at("y").asFloat();
	player->GetSpriteBack()->setPosition(x*this->m_tiledmap->getScaleX(), y*this->m_tiledmap->getScaleY());
	this->addChild(player->GetSpriteBack(), 10);
	x = obj->getObject("opponent").at("x").asFloat();
	y = obj->getObject("opponent").at("y").asFloat();
	opponent->GetSpriteFront()->setPosition(x*this->m_tiledmap->getScaleX(), y*this->m_tiledmap->getScaleY());
	this->addChild(opponent->GetSpriteFront(), 10);
}

void BattleScene::DamagePhase(int idSkill)
{
	if (this->player->GetAtkSpeed() >= this->opponent->GetAtkSpeed())
	{
		this->m_labelBattleLog->setString(this->player->GetName() + " used " + this->player->GetSkillById(idSkill)->GetName());
		this->player->Attack(this->opponent, this->player->GetSkillById(idSkill));
		auto finished = CallFunc::create([&]() {
			this->m_labelOppHealth->setString(to_string(this->opponent->GetCurrentHP()) + "/" + to_string(this->opponent->GetMaxHP()));
			if (this->opponent->IsAlive())
			{
				int id = rand() % this->opponent->GetCountSkills();
				this->m_labelBattleLog->setString(this->opponent->GetName() + " used " + this->opponent->GetSkillById(id)->GetName());
				this->opponent->Attack(this->player, this->opponent->GetSkillById(id));
				auto done = CallFunc::create([&]() {
					this->m_buttonFight->setVisible(true);
					this->m_buttonBag->setVisible(true);
					this->m_buttonPokemon->setVisible(true);
					this->m_buttonRun->setVisible(true);
					this->m_labelSkill1->setString("Fight");
					this->m_labelSkill2->setString("Bag");
					this->m_labelSkill3->setString("Pokemon");
					this->m_labelSkill4->setString("Run");
				});
				this->runAction(Sequence::create(DelayTime::create(4), done, nullptr));
			}
		});
		this->runAction(Sequence::create(DelayTime::create(4), finished, nullptr));
	}
	else
	{
		int id = rand() % this->opponent->GetCountSkills();
		this->m_labelBattleLog->setString(this->opponent->GetName() + " used " + this->opponent->GetSkillById(id)->GetName());
		this->opponent->Attack(this->player, this->opponent->GetSkillById(id));
		auto finished = CallFunc::create([&]() {
			if (this->player->IsAlive())
			{
				this->m_labelBattleLog->setString(this->player->GetName() + " used " + this->player->GetSkillById(idSkill)->GetName());
				this->player->Attack(this->opponent, this->player->GetSkillById(idSkill));
				auto done = CallFunc::create([&]() {
					this->m_labelOppHealth->setString(to_string(this->opponent->GetCurrentHP()) + "/" + to_string(this->opponent->GetMaxHP()));
					this->m_buttonFight->setVisible(true);
					this->m_buttonBag->setVisible(true);
					this->m_buttonPokemon->setVisible(true);
					this->m_buttonRun->setVisible(true);
					this->m_labelSkill1->setString("Fight");
					this->m_labelSkill2->setString("Bag");
					this->m_labelSkill3->setString("Pokemon");
					this->m_labelSkill4->setString("Run");
				});
				this->runAction(Sequence::create(DelayTime::create(4), done, nullptr));
			}
		});
		this->runAction(Sequence::create(DelayTime::create(3), finished, nullptr));
	}
}