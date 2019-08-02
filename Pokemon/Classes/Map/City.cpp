#include "City.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "Route1.h"
#include "PokemonCenter.h"
#include "Lake.h"
#include "Cave.h"
#include "Route2.h"
#include "Model.h"
#include "Scene\BattleScene.h"
#include <cstdlib>
#include "Popup.h"

using namespace CocosDenshion;
USING_NS_CC;
Size cityVisibleSize;
Size cityTileMapSize;
vector<Pokemon*> listNpcPokemon;
Layer *layer_UI_City;
Camera *cityCamera, *cameraUICity;
PhysicsBody* cityBody, *cityGateWay, *lakenpcbody, *cavenpcbody, *route2npcbody;
int City::previousScene = 0;
bool npc_state = true;



Scene* City::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = City::create();
	scene->addChild(layer);
	cityCamera = scene->getDefaultCamera();
	return scene;
}

void City::TypeWriter(float deltaTime)
{
	if (writing < this->m_labelLog->getStringLength())
	{
		auto letter = this->m_labelLog->getLetter(writing);
		if (letter != nullptr)
		{
			letter->setOpacity(255);
		}
		writing++;
	}
	else
	{
		writing = 0;
		this->m_labelLog->setOpacity(255);
		this->unschedule(schedule_selector(City::TypeWriter));
	}
}

void City::LogSetOpacity(GLubyte opacity)
{
	for (int i = 0; i < this->m_labelLog->getStringLength(); i++)
	{
		auto letter = this->m_labelLog->getLetter(i);
		if (letter != nullptr)
		{
			letter->setOpacity(opacity);
		}
	}
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool City::init()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Sound/CityScene.mp3", true);
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	cityVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/City.tmx");
	cityTileMapSize = map->getContentSize();
	addChild(map);
	auto mPhysicsLayer = map->getLayer("physics");
	Size layerSize = mPhysicsLayer->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = mPhysicsLayer->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physics = PhysicsBody::createBox(tileSet->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				physics->setCollisionBitmask(Model::BITMASK_WORLD);
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				physics->setGravityEnable(false);
				tileSet->setPhysicsBody(physics);
			}
		}
	}

	InitObject();

	Button *up = Buttons::GetIntance()->GetButtonUp();
	Button *bag = Buttons::GetIntance()->GetButtonBag();
	Button *tips = Buttons::GetIntance()->GetButtonTips();

	layer_UI_City = Layer::create();
	cameraUICity = Camera::create();
	cameraUICity->setCameraMask(2);
	cameraUICity->setCameraFlag(CameraFlag::USER1);
	up->setCameraMask(2);
	bag->setCameraMask(2);
	tips->setCameraMask(2);
	layer_UI_City->addChild(cameraUICity, 2);
	layer_UI_City->addChild(up);
	layer_UI_City->addChild(bag);
	layer_UI_City->addChild(tips);
	this->addChild(layer_UI_City, 100);

	Buttons::GetIntance()->ButtonListener(this->mPlayer);

	Buttons::GetIntance()->GetButtonBag()->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(false);
			string str = "My bag - Gold: " + to_string(Bag::GetInstance()->GetGold()) + " $";
			UICustom::Popup *popup = UICustom::Popup::createBag(str);
			popup->removeFromParent();
			popup->setAnchorPoint(Vec2(0.5, 0.5));
			popup->setPosition(cityCamera->getPosition().x - popup->getContentSize().width / 2,
				cityCamera->getPosition().y - popup->getContentSize().height / 2);
			this->addChild(popup, 101);
		}
	});

	Buttons::GetIntance()->GetButtonTips()->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Buttons::GetIntance()->GetButtonTips()->setTouchEnabled(false);
			UICustom::Popup *popup = UICustom::Popup::createAsMessage("Doctor", Model::GetTipsGame());
			popup->removeFromParent();
			popup->setAnchorPoint(Vec2(0.5, 0.5));
			popup->setPosition(cityCamera->getPosition().x - popup->getContentSize().width / 2,
				cityCamera->getPosition().y - popup->getContentSize().height / 2);
			this->addChild(popup, 101);
		}
	});
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(City::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	this->m_messageBox = ResourceManager::GetInstance()->GetSpriteById(130);
	auto scale_x = 0.7;
	auto scale_y = 0.7;
	this->m_messageBox->setScaleX(scale_x);
	this->m_messageBox->setScaleY(scale_y);
	this->m_messageBox->setVisible(false);
	this->m_messageBox->setPosition(Director::getInstance()->getVisibleSize().width / 1.76, Director::getInstance()->getVisibleSize().height / 1.5);
	this->addChild(this->m_messageBox, 10);
	this->m_labelLog = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelLog->setAnchorPoint(Vec2::ZERO);
	this->m_labelLog->setScale(1.5);
	this->m_labelLog->setTextColor(Color4B::BLACK);
	this->m_labelLog->setPosition(this->m_messageBox->getContentSize().width * scale_x / 10, this->m_messageBox->getContentSize().height * scale_y / 1.2);
	this->m_messageBox->addChild(this->m_labelLog);
	return true;
}

bool City::onContactBegin(PhysicsContact& contact)

{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_ROUTE1)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_ROUTE1 && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_ROUTE1_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route1::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_PC)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_PC && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_PC_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PokemonCenter::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_CAVE)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_CAVE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_CAVE_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Cave::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_LAKE)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_LAKE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_LAKE_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Lake::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_ROUTE2)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_ROUTE2 && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_ROUTE2_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route2::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_WORLD && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WORLD))
	{
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/WallBump.mp3", false);
		switch (Buttons::state)
		{
		case 1:
			mPlayer->GetSpriteFront()->stopActionByTag(0);
			mPlayer->GetSpriteFront()->setPositionY(mPlayer->GetSpriteFront()->getPositionY() - 2);
			break;
		case 2:
			mPlayer->GetSpriteFront()->stopActionByTag(6);
			mPlayer->GetSpriteFront()->setPositionX(mPlayer->GetSpriteFront()->getPositionX() - 2);
			break;
		case 3:
			mPlayer->GetSpriteFront()->stopActionByTag(4);
			mPlayer->GetSpriteFront()->setPositionX(mPlayer->GetSpriteFront()->getPositionX() + 2);
			break;
		case 4:
			mPlayer->GetSpriteFront()->stopActionByTag(2);
			mPlayer->GetSpriteFront()->setPositionY(mPlayer->GetSpriteFront()->getPositionY() + 2);
			break;
		default:
			break;
		}
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_LAKENPC && Bag::GetInstance()->GetCountPokemon() > 0)
		|| a->getCollisionBitmask() == Model::BITMASK_LAKENPC && b->getCollisionBitmask() == Model::BITMASK_PLAYER && Bag::GetInstance()->GetCountPokemon() > 0)
	{
		switch (Buttons::state)
		{
		case 1:
			mPlayer->StopWalkUp();
			break;
		case 2:
			mPlayer->StopWalkRight();
			break;
		case 3:
			mPlayer->StopWalkLeft();
			break;
		case 4:
			mPlayer->StopWalkDown();
			break;
		default:
			break;
		}
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/Beep.mp3", false);
		Buttons::GetIntance()->SetVisible(false);
		this->Log("Let's battle!");
		this->m_messageBox->setVisible(true);
		touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(City::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		listNpcPokemon = this->m_lakenpc->GetListPokemon();
		auto listener = CallFunc::create([this]() {
			if (npc_state == false)
			{
				Model::LAKENPC = false;
				this->m_lakenpc->GetSpriteFront()->removeFromParent();
				npc_state = true;
				this->stopActionByTag(100);
			}
		});
		auto rp = RepeatForever::create(Spawn::create(listener, nullptr));
		rp->setTag(100);
		this->runAction(rp);
		//removeChild(m_lakenpc, true);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CAVENPC && Bag::GetInstance()->GetCountPokemon() > 0)
		|| a->getCollisionBitmask() == Model::BITMASK_CAVENPC && b->getCollisionBitmask() == Model::BITMASK_PLAYER && Bag::GetInstance()->GetCountPokemon() > 0)
	{
		switch (Buttons::state)
		{
		case 1:
			mPlayer->StopWalkUp();
			break;
		case 2:
			mPlayer->StopWalkRight();
			break;
		case 3:
			mPlayer->StopWalkLeft();
			break;
		case 4:
			mPlayer->StopWalkDown();
			break;
		default:
			break;
		}
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/Beep.mp3", false);
		Buttons::GetIntance()->SetVisible(false);
		this->Log("ZzzzZzzzZZzz");
		this->m_messageBox->setVisible(true);
		touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(City::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		listNpcPokemon = this->m_cavenpc->GetListPokemon();
		auto listener = CallFunc::create([this]() {
			if (npc_state == false)
			{
				Model::CAVENPC = false;
				this->m_cavenpc->GetSpriteFront()->removeFromParent();
				npc_state = true;
				this->stopActionByTag(100);
			}
		});
		auto rp = RepeatForever::create(Spawn::create(listener, nullptr));
		rp->setTag(100);
		this->runAction(rp);
		//removeChild(m_cavenpc, true);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROUTE2NPC && Bag::GetInstance()->GetCountPokemon() > 0)
		|| a->getCollisionBitmask() == Model::BITMASK_ROUTE2NPC && b->getCollisionBitmask() == Model::BITMASK_PLAYER && Bag::GetInstance()->GetCountPokemon() > 0)
	{
		switch (Buttons::state)
		{
		case 1:
			mPlayer->StopWalkUp();
			break;
		case 2:
			mPlayer->StopWalkRight();
			break;
		case 3:
			mPlayer->StopWalkLeft();
			break;
		case 4:
			mPlayer->StopWalkDown();
			break;
		default:
			break;
		}
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/Beep.mp3", false);
		Buttons::GetIntance()->SetVisible(false);
		this->Log("Let's battle!");
		this->m_messageBox->setVisible(true);
		touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(City::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		listNpcPokemon = this->m_route2npc->GetListPokemon();
		auto listener = CallFunc::create([this]() {
			if (npc_state == false)
			{
				Model::ROUTE2NPC = false;
				this->m_route2npc->GetSpriteFront()->removeFromParent();
				npc_state = true;
				this->stopActionByTag(100);
			}
		});
		auto rp = RepeatForever::create(Spawn::create(listener, nullptr));
		rp->setTag(100);
		this->runAction(rp);
		//removeChild(m_route2npc, true);
	}
	return true;
}

void City::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/City.tmx");
	auto m_objectGroup = map->getObjectGroup("Object");
	auto objects = m_objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++) {
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == Model::MODLE_TYPE_MAIN_CHARACTER) {
			int preScene = object.asValueMap().at("pre").asInt();
			if (preScene == previousScene) {
				mPlayer = new Trainer(this);
				if (preScene == 1)
				{
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkdown/1.png");
				}
				else if (preScene == 2)
				{
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkright/1.png");
				}
				else if (preScene == 3)
				{
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkleft/1.png");
				}
				else if (preScene == 4)
				{
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkdown/1.png");
				}
				mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
				cityBody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				cityBody->setCollisionBitmask(Model::BITMASK_PLAYER);
				cityBody->setContactTestBitmask(true);
				cityBody->setDynamic(true);
				cityBody->setRotationEnable(false);
				cityBody->setGravityEnable(false);
				mPlayer->GetSpriteFront()->setPhysicsBody(cityBody);
			}
			else continue;
		}
		else if (type == Model::MODLE_TYPE_CITY_GATE_TO_ROUTE1)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			cityGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			cityGateWay->setCollisionBitmask(Model::BITMASK_CITY_GATE_TO_ROUTE1);
			cityGateWay->setContactTestBitmask(true);
			cityGateWay->setDynamic(false);
			cityGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(cityGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_CITY_GATE_TO_PC)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			cityGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			cityGateWay->setCollisionBitmask(Model::BITMASK_CITY_GATE_TO_PC);
			cityGateWay->setContactTestBitmask(true);
			cityGateWay->setDynamic(false);
			cityGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(cityGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_CITY_GATE_TO_CAVE)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			cityGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			cityGateWay->setCollisionBitmask(Model::BITMASK_CITY_GATE_TO_CAVE);
			cityGateWay->setContactTestBitmask(true);
			cityGateWay->setDynamic(false);
			cityGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(cityGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_CITY_GATE_TO_LAKE)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			cityGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			cityGateWay->setCollisionBitmask(Model::BITMASK_CITY_GATE_TO_LAKE);
			cityGateWay->setContactTestBitmask(true);
			cityGateWay->setDynamic(false);
			cityGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(cityGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_CITY_GATE_TO_ROUTE2)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			cityGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			cityGateWay->setCollisionBitmask(Model::BITMASK_CITY_GATE_TO_ROUTE2);
			cityGateWay->setContactTestBitmask(true);
			cityGateWay->setDynamic(false);
			cityGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(cityGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if(type == Model::MODLE_TYPE_LAKENPC)
		{
			m_lakenpc = new LakeNPC();
			if (Model::LAKENPC == true)
			{
				m_lakenpc->GetSpriteFront()->setPosition(Vec2(posX, posY));
				m_lakenpc->GetSpriteFront()->setScale(0.8);
				lakenpcbody = PhysicsBody::createBox(m_lakenpc->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				lakenpcbody->setCollisionBitmask(Model::BITMASK_LAKENPC);
				lakenpcbody->setContactTestBitmask(true);
				lakenpcbody->setDynamic(false);
				lakenpcbody->setGravityEnable(false);
				m_lakenpc->GetSpriteFront()->setPhysicsBody(lakenpcbody);
				this->addChild(m_lakenpc->GetSpriteFront(), 10);
			}
		}
		else if (type == Model::MODLE_TYPE_CAVENPC)
		{
			m_cavenpc = new CaveNPC();
			if (Model::CAVENPC == true)
			{
				m_cavenpc->GetSpriteFront()->setPosition(Vec2(posX, posY));
				m_cavenpc->GetSpriteFront()->setScale(1.2);
				cavenpcbody = PhysicsBody::createBox(m_cavenpc->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				cavenpcbody->setCollisionBitmask(Model::BITMASK_CAVENPC);
				cavenpcbody->setContactTestBitmask(true);
				cavenpcbody->setDynamic(false);
				cavenpcbody->setGravityEnable(false);
				m_cavenpc->GetSpriteFront()->setPhysicsBody(cavenpcbody);
				this->addChild(m_cavenpc->GetSpriteFront(), 10);
			}
		}
		else if (type == Model::MODLE_TYPE_ROUTE2NPC)
		{
			m_route2npc = new Route2NPC();
			if (Model::ROUTE2NPC == true)
			{
				m_route2npc->GetSpriteFront()->setPosition(Vec2(posX, posY));
				m_route2npc->GetSpriteFront()->setScale(0.8);
				route2npcbody = PhysicsBody::createBox(m_route2npc->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				route2npcbody->setCollisionBitmask(Model::BITMASK_ROUTE2NPC);
				route2npcbody->setContactTestBitmask(true);
				route2npcbody->setDynamic(false);
				route2npcbody->setGravityEnable(false);
				m_route2npc->GetSpriteFront()->setPhysicsBody(route2npcbody);
				this->addChild(m_route2npc->GetSpriteFront(), 10);
			}
		}
	}
}

void City::UpdateCamera() {
	if (cityVisibleSize.width >= cityTileMapSize.width) {
		if (cityVisibleSize.height >= cityTileMapSize.height) {
			cityCamera->setPosition(cityTileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - cityTileMapSize.height / 2)>abs(cityTileMapSize.height / 2 - cityVisibleSize.height / 2)) {
				cityCamera->setPosition(cityTileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >cityCamera->getPosition().y) ? (cityTileMapSize.height - cityVisibleSize.height / 2) : cityVisibleSize.height / 2);
			}
			else {
				cityCamera->setPosition(cityTileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (cityVisibleSize.height >= cityTileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - cityTileMapSize.width / 2)>abs(cityTileMapSize.width / 2 - cityVisibleSize.width / 2)) {
				cityCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >cityCamera->getPosition().y) ? (cityTileMapSize.width - cityVisibleSize.width / 2) : cityVisibleSize.width / 2, cityTileMapSize.height / 2);
			}
			else {
				cityCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, cityTileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - cityTileMapSize.width / 2)>abs(cityTileMapSize.width / 2 - cityVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - cityTileMapSize.height / 2)>abs(cityTileMapSize.height / 2 - cityVisibleSize.height / 2)) {
				cityCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >cityCamera->getPosition().x) ? (cityTileMapSize.width - cityVisibleSize.width / 2) : cityVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >cityCamera->getPosition().y) ? (cityTileMapSize.height - cityVisibleSize.height / 2) : cityVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - cityTileMapSize.width / 2)>abs(cityTileMapSize.width / 2 - cityVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - cityTileMapSize.height / 2)<abs(cityTileMapSize.height / 2 - cityVisibleSize.height / 2)) {
				cityCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >cityCamera->getPosition().x) ? (cityTileMapSize.width - cityVisibleSize.width / 2) : cityVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - cityTileMapSize.width / 2)<abs(cityTileMapSize.width / 2 - cityVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - cityTileMapSize.height / 2)>abs(cityTileMapSize.height / 2 - cityVisibleSize.height / 2)) {
				cityCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >cityCamera->getPosition().y) ? (cityTileMapSize.height - cityVisibleSize.height / 2) : cityVisibleSize.height / 2);
			}
			else {
				cityCamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}

int citySum = 0;
void City::UpdatePlayer(float dt) {
	citySum++;
	if (citySum  >30) {
		if (mPlayer->isMoveDown) {
			mPlayer->StopWalkDown();
			mPlayer->WalkDown();
		}
		else if (mPlayer->isMoveLeft) {
			mPlayer->StopWalkLeft();
			mPlayer->WalkLeft();
		}
		else if (mPlayer->isMoveUp) {
			mPlayer->StopWalkUp();
			mPlayer->WalkUp();
		}
		else if (mPlayer->isMoveRight) {
			mPlayer->StopWalkRight();
			mPlayer->WalkRight();
		}
		else
		{
		}
		citySum = 0;
	}
}


void City::Log(string logg)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Beep.mp3", false);
	this->m_labelLog->setString(logg);
	this->LogSetOpacity(0);
	this->m_labelLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(City::TypeWriter), 0.05);
}

bool City::onTouchBegan(Touch * touch, Event * e)
{
	if (this->m_labelLog->getOpacity() == 0)
	{
		this->unschedule(schedule_selector(City::TypeWriter));
		this->LogSetOpacity(255);
		this->m_labelLog->setOpacity(255);
		/*touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(City::onTouchEnd, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);*/
	}
	else
	{
		this->m_messageBox->setVisible(false);
		auto layer = BattleScene::CreateLayer(listNpcPokemon);
		layer->setPosition(cityCamera->getPosition().x - Director::getInstance()->getVisibleSize().width / 2,
			cityCamera->getPosition().y - Director::getInstance()->getVisibleSize().height / 2);
		this->addChild(layer, 1000);
		this->unscheduleUpdate();
		//Buttons::GetIntance()->SetVisible(false);
		Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
	}
	return true;
}

bool City::onTouchEnd(Touch * t, Event * event)
{
	/*this->m_messageBox->setVisible(false);
	Buttons::GetIntance()->SetTouchEnable();*/
	return true;
}

void City::update(float dt) {
	if (this->getTag() == 10)
	{
		npc_state = false;
	}
	UpdatePlayer(dt);
	UpdateCamera();
	this->setTag(0);
}