
#include "Route2.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "City.h"
#include "Model.h"
#include "VictoryRoad.h"

using namespace CocosDenshion;
Size route2VisibleSize;
Size route2TileMapSize;

PhysicsBody* route2Body, *route2GateWay;
Camera *route2Camera;
int Route2::previousScene = 0;

Scene* Route2::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Route2::create();
	scene->addChild(layer);
	route2Camera = scene->getDefaultCamera();
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Route2::init()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Sound/Route2.mp3", true);
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	route2VisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = ResourceManager::GetInstance()->GetTiledMapById(10);
	route2TileMapSize = map->getContentSize();
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
	Button *right = Buttons::GetIntance()->GetButtonRight();
	Button *left = Buttons::GetIntance()->GetButtonLeft();
	Button *down = Buttons::GetIntance()->GetButtonDown();
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);

	Buttons::GetIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Route2::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Route2::onContactBegin(PhysicsContact& contact)

{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROUTE2_GATE_TO_CITY)
		|| a->getCollisionBitmask() == Model::MODLE_TYPE_ROUTE2_GATE_TO_CITY && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Route2::previousScene = Model::PRESCENE_CITY_TO_ROUTE2;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, City::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROUTE2_GATE_TO_ROAD)
		|| a->getCollisionBitmask() == Model::BITMASK_ROUTE2_GATE_TO_ROAD && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{
		Buttons::GetIntance()->Remove();
		Route2::previousScene = Model::PRESCENE_ROAD_TO_ROUTE2;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Road::createScene()));
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
	return true;

}

void Route2::InitObject()
{
	auto map = ResourceManager::GetInstance()->GetTiledMapById(10);
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
				route2Body = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				route2Body->setCollisionBitmask(Model::BITMASK_PLAYER);
				route2Body->setContactTestBitmask(true);
				route2Body->setDynamic(true);
				route2Body->setRotationEnable(false);
				route2Body->setGravityEnable(false);
				mPlayer->GetSpriteFront()->setPhysicsBody(route2Body);
			}
			else continue;
		}
		else if (type == Model::MODLE_TYPE_ROUTE2_GATE_TO_CITY)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			route2GateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			route2GateWay->setCollisionBitmask(Model::BITMASK_ROUTE2_GATE_TO_CITY);
			route2GateWay->setContactTestBitmask(true);
			route2GateWay->setDynamic(false);
			route2GateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(route2GateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_ROUTE2_GATE_TO_ROAD)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			route2GateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			route2GateWay->setCollisionBitmask(Model::BITMASK_ROUTE2_GATE_TO_ROAD);
			route2GateWay->setContactTestBitmask(true);
			route2GateWay->setDynamic(false);
			route2GateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(route2GateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}
}

void Route2::UpdateCamera() {
	if (route2VisibleSize.width >= route2TileMapSize.width) {
		if (route2VisibleSize.height >= route2TileMapSize.height) {
			route2Camera->setPosition(route2TileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - route2TileMapSize.height / 2)>abs(route2TileMapSize.height / 2 - route2VisibleSize.height / 2)) {
				route2Camera->setPosition(route2TileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >route2Camera->getPosition().y) ? (route2TileMapSize.height - route2VisibleSize.height / 2) : route2VisibleSize.height / 2);
			}
			else {
				route2Camera->setPosition(route2TileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (route2VisibleSize.height >= route2TileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - route2TileMapSize.width / 2)>abs(route2TileMapSize.width / 2 - route2VisibleSize.width / 2)) {
				route2Camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >route2Camera->getPosition().y) ? (route2TileMapSize.width - route2VisibleSize.width / 2) : route2VisibleSize.width / 2, route2TileMapSize.height / 2);
			}
			else {
				route2Camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, route2TileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - route2TileMapSize.width / 2)>abs(route2TileMapSize.width / 2 - route2VisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - route2TileMapSize.height / 2)>abs(route2TileMapSize.height / 2 - route2VisibleSize.height / 2)) {
				route2Camera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >route2Camera->getPosition().x) ? (route2TileMapSize.width - route2VisibleSize.width / 2) : route2VisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >route2Camera->getPosition().y) ? (route2TileMapSize.height - route2VisibleSize.height / 2) : route2VisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - route2TileMapSize.width / 2)>abs(route2TileMapSize.width / 2 - route2VisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - route2TileMapSize.height / 2)<abs(route2TileMapSize.height / 2 - route2VisibleSize.height / 2)) {
				route2Camera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >route2Camera->getPosition().x) ? (route2TileMapSize.width - route2VisibleSize.width / 2) : route2VisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - route2TileMapSize.width / 2)<abs(route2TileMapSize.width / 2 - route2VisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - route2TileMapSize.height / 2)>abs(route2TileMapSize.height / 2 - route2VisibleSize.height / 2)) {
				route2Camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >route2Camera->getPosition().y) ? (route2TileMapSize.height - route2VisibleSize.height / 2) : route2VisibleSize.height / 2);
			}
			else {
				route2Camera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}

void Route2::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(route2Camera->getPosition().x - 200, route2Camera->getPosition().y - 100);
}