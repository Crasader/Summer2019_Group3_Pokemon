
#include "Route1.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "Town.h"
#include "City.h"
#include "Model.h"

using namespace CocosDenshion;
Size route1VisibleSize;
Size route1TileMapSize;

Layer *layer_UI_Route1;

PhysicsBody* route1Body, *route1GateWay, *route1npcbody;
Camera *route1Camera, *cameraUIRoute1;
int Route1::previousScene = 0;

Scene* Route1::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Route1::create();
	scene->addChild(layer);
	route1Camera = scene->getDefaultCamera();
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Route1::init()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Sound/Route1.mp3", true);
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	route1VisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto map = ResourceManager::GetInstance()->GetTiledMapById(4);
	route1TileMapSize = map->getContentSize();
	auto mapTree = ResourceManager::GetInstance()->GetTiledMapById(5);
	auto mapTree1 = ResourceManager::GetInstance()->GetTiledMapById(6);
	addChild(map);
	addChild(mapTree, 20);
	addChild(mapTree1, 5);

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

	auto grass = map->getLayer("grass");
	int count = 0;
	Size layerSize2 = grass->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize2.height; j++)
		{
			auto tilePokemon = grass->getTileAt(Vec2(i, j));
			if (tilePokemon != NULL)
			{
				if (count < 10) {
					int _random = rand() % 15;
					if (!_random) {
						auto pokemon = PhysicsBody::createBox(tilePokemon->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
						pokemon->setCollisionBitmask(Model::BITMASK_POKEMON);
						pokemon->setContactTestBitmask(true);
						pokemon->setDynamic(false);
						pokemon->setGravityEnable(false);
						tilePokemon->setPhysicsBody(pokemon);
						count++;
					}
				}
			}
		}
	}

	InitObject();
	
	Button *up = Buttons::GetIntance()->GetButtonUp();
	Button *bag = Buttons::GetIntance()->GetButtonBag();
	Button *tips = Buttons::GetIntance()->GetButtonTips();

	layer_UI_Route1 = Layer::create();
	cameraUIRoute1 = Camera::create();
	cameraUIRoute1->setCameraMask(2);
	cameraUIRoute1->setCameraFlag(CameraFlag::USER1);
	up->setCameraMask(2);
	bag->setCameraMask(2);
	tips->setCameraMask(2);
	layer_UI_Route1->addChild(cameraUIRoute1, 2);
	layer_UI_Route1->addChild(up);
	layer_UI_Route1->addChild(bag);
	layer_UI_Route1->addChild(tips);
	this->addChild(layer_UI_Route1, 100);

	Buttons::GetIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Route1::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	this->m_messageBox = ResourceManager::GetInstance()->GetSpriteById(130);
	auto scale_x = 0.7;
	auto scale_y = 0.7;
	this->m_messageBox->setScaleX(scale_x);
	this->m_messageBox->setScaleY(scale_y);
	this->m_messageBox->setVisible(false);
	this->m_messageBox->setPosition(Director::getInstance()->getVisibleSize().width / 1.76, Director::getInstance()->getVisibleSize().height / 1.5);
	this->addChild(this->m_messageBox, 100);
	this->m_labelLog = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelLog->setAnchorPoint(Vec2::ZERO);
	this->m_labelLog->setScale(1.5);
	this->m_labelLog->setTextColor(Color4B::BLACK);
	this->m_labelLog->setPosition(this->m_messageBox->getContentSize().width * scale_x / 10, this->m_messageBox->getContentSize().height * scale_y / 1.2);
	this->m_messageBox->addChild(this->m_labelLog);
	return true;
}

void Route1::TypeWriter(float deltaTime)
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
		this->unschedule(schedule_selector(Route1::TypeWriter));
	}
}

void Route1::LogSetOpacity(GLubyte opacity)
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

bool Route1::onContactBegin(PhysicsContact& contact)

{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROUTE1_GATE_TO_TOWN)
		|| a->getCollisionBitmask() == Model::BITMASK_ROUTE1_GATE_TO_TOWN && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Town::previousScene = Model::PRESCENE_ROUTE1_TO_TOWN;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Town::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROUTE1_GATE_TO_CITY)
		|| a->getCollisionBitmask() == Model::BITMASK_ROUTE1_GATE_TO_CITY && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{

		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_ROUTE1_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, City::createScene()));
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
			mPlayer->GetSpriteFront()->setPositionY(mPlayer->GetSpriteFront()->getPositionY() - 1);
			break;
		case 2:
			mPlayer->GetSpriteFront()->stopActionByTag(6);
			mPlayer->GetSpriteFront()->setPositionX(mPlayer->GetSpriteFront()->getPositionX() - 1);
			break;
		case 3:
			mPlayer->GetSpriteFront()->stopActionByTag(4);
			mPlayer->GetSpriteFront()->setPositionX(mPlayer->GetSpriteFront()->getPositionX() + 1);
			break;
		case 4:
			mPlayer->GetSpriteFront()->stopActionByTag(2);
			mPlayer->GetSpriteFront()->setPositionY(mPlayer->GetSpriteFront()->getPositionY() + 1);
			break;
		default:
			break;
		}
	}
	/*else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROUTE1NPC)
		|| a->getCollisionBitmask() == Model::BITMASK_ROUTE1NPC && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
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
		audio->playEffect("Beep.mp3", false);
		Buttons::GetIntance()->SetTouchDisable();
		this->Log("Let's battle!");
		this->m_messageBox->setVisible(true);
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Route1::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		Model::ROUTE1NPC = false;
	}
		removeChild(m_route1npc, true);
	}*/
	return true;
}

void Route1::InitObject()
{
	auto map = ResourceManager::GetInstance()->GetTiledMapById(4);
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
				mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
				route1Body = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				route1Body->setCollisionBitmask(Model::BITMASK_PLAYER);
				route1Body->setContactTestBitmask(true);
				route1Body->setDynamic(true);
				route1Body->setRotationEnable(false);
				route1Body->setGravityEnable(false);
				mPlayer->GetSpriteFront()->setPhysicsBody(route1Body);
			}
			else continue;
		}
		else if (type == Model::MODLE_TYPE_ROUTE1_GATE_TO_TOWN)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			route1GateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			route1GateWay->setCollisionBitmask(Model::BITMASK_ROUTE1_GATE_TO_TOWN);
			route1GateWay->setContactTestBitmask(true);
			route1GateWay->setDynamic(false);
			route1GateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(route1GateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_ROUTE1_GATE_TO_CITY)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			route1GateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			route1GateWay->setCollisionBitmask(Model::BITMASK_ROUTE1_GATE_TO_CITY);
			route1GateWay->setContactTestBitmask(true);
			route1GateWay->setDynamic(false);
			route1GateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(route1GateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		/*else if (type == Model::MODLE_TYPE_ROUTE1NPC)
		{
			if (Model::ROUTE1NPC == true)
			{
				m_route1npc = ResourceManager::GetInstance()->GetSpriteById(123);
				m_route1npc->setPosition(Vec2(posX, posY));
				m_route1npc->setScale(0.8);
				route1npcbody = PhysicsBody::createBox(m_route1npc->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				route1npcbody->setCollisionBitmask(Model::BITMASK_ROUTE1NPC);
				route1npcbody->setContactTestBitmask(true);
				route1npcbody->setDynamic(false);
				route1npcbody->setGravityEnable(false);
				m_route1npc->setPhysicsBody(route1npcbody);
				this->addChild(m_route1npc, 10);
			}
		}*/
	}
}

void Route1::UpdateCamera() {
	if (route1VisibleSize.width >= route1TileMapSize.width) {
		if (route1VisibleSize.height >= route1TileMapSize.height) {
			route1Camera->setPosition(route1TileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - route1TileMapSize.height / 2)>abs(route1TileMapSize.height / 2 - route1VisibleSize.height / 2)) {
				route1Camera->setPosition(route1TileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >route1Camera->getPosition().y) ? (route1TileMapSize.height - route1VisibleSize.height / 2) : route1VisibleSize.height / 2);
			}
			else {
				route1Camera->setPosition(route1TileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (route1VisibleSize.height >= route1TileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - route1TileMapSize.width / 2)>abs(route1TileMapSize.width / 2 - route1VisibleSize.width / 2)) {
				route1Camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >route1Camera->getPosition().y) ? (route1TileMapSize.width - route1VisibleSize.width / 2) : route1VisibleSize.width / 2, route1TileMapSize.height / 2);
			}
			else {
				route1Camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, route1TileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - route1TileMapSize.width / 2)>abs(route1TileMapSize.width / 2 - route1VisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - route1TileMapSize.height / 2)>abs(route1TileMapSize.height / 2 - route1VisibleSize.height / 2)) {
				route1Camera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >route1Camera->getPosition().x) ? (route1TileMapSize.width - route1VisibleSize.width / 2) : route1VisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >route1Camera->getPosition().y) ? (route1TileMapSize.height - route1VisibleSize.height / 2) : route1VisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - route1TileMapSize.width / 2)>abs(route1TileMapSize.width / 2 - route1VisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - route1TileMapSize.height / 2)<abs(route1TileMapSize.height / 2 - route1VisibleSize.height / 2)) {
				route1Camera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >route1Camera->getPosition().x) ? (route1TileMapSize.width - route1VisibleSize.width / 2) : route1VisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - route1TileMapSize.width / 2)<abs(route1TileMapSize.width / 2 - route1VisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - route1TileMapSize.height / 2)>abs(route1TileMapSize.height / 2 - route1VisibleSize.height / 2)) {
				route1Camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >route1Camera->getPosition().y) ? (route1TileMapSize.height - route1VisibleSize.height / 2) : route1VisibleSize.height / 2);
			}
			else {
				route1Camera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}

void Route1::Log(string logg)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Beep.mp3", false);
	this->m_labelLog->setString(logg);
	this->LogSetOpacity(0);
	this->m_labelLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(Route1::TypeWriter), 0.05);
}

bool Route1::onTouchBegan(Touch * touch, Event * e)
{
	if (this->m_labelLog->getOpacity() == 0)
	{
		this->unschedule(schedule_selector(Route1::TypeWriter));
		this->LogSetOpacity(255);
		this->m_labelLog->setOpacity(255);
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Route1::onTouchEnd, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	}
	return true;
}

int route1Sum = 0;

void Route1::UpdatePlayer(float dt) {
	route1Sum++;
	if (route1Sum >30) {
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
		route1Sum = 0;
	}
}

bool Route1::onTouchEnd(Touch * t, Event * event)
{
	this->m_messageBox->setVisible(false);
	removeChild(m_route1npc, true);
	Buttons::GetIntance()->SetTouchEnable();
	return true;
}

void Route1::update(float dt) {
	UpdateCamera();
	UpdatePlayer(dt);
}
