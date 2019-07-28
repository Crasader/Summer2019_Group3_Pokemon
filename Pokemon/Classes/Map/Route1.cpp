
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

PhysicsBody* route1Body, *route1GateWay;
Camera *route1Camera;
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
	Button *right = Buttons::GetIntance()->GetButtonRight();
	Button *left = Buttons::GetIntance()->GetButtonLeft();
	Button *down = Buttons::GetIntance()->GetButtonDown();
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);
	Buttons::GetIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Route1::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
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
		Route1::previousScene = Model::PRESCENE_TOWN_TO_ROUTE1;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Town::createScene()));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROUTE1_GATE_TO_CITY)
		|| a->getCollisionBitmask() == Model::BITMASK_ROUTE1_GATE_TO_CITY && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{

		Buttons::GetIntance()->Remove();
		Route1::previousScene = Model::PRESCENE_CITY_TO_ROUTE1;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, City::createScene()));
	}
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

void Route1::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(route1Camera->getPosition().x - 200, route1Camera->getPosition().y - 100);
}