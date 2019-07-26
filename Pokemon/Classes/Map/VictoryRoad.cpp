
#include "VictoryRoad.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "Route2.h"
#include "Model.h"
#include "ChampionLeague.h"

using namespace CocosDenshion;
Size roadVisibleSize;
Size roadTileMapSize;

PhysicsBody* roadBody, *roadGateWay;
Camera *roadCamera;

Scene* Road::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Road::create();
	scene->addChild(layer);
	roadCamera = scene->getDefaultCamera();
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Road::init()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Sound/VictoryRoad.mp3", true);
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	roadVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/Road.tmx");
	roadTileMapSize = map->getContentSize();
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
	Button *right = Buttons::GetIntance()->GetButtonRight();
	Button *left = Buttons::GetIntance()->GetButtonLeft();
	Button *down = Buttons::GetIntance()->GetButtonDown();
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);

	Buttons::GetIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Road::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Road::onContactBegin(PhysicsContact& contact)

{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROAD_GATE_TO_ROUTE2)
		|| a->getCollisionBitmask() == Model::BITMASK_ROAD_GATE_TO_ROUTE2 && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route2::createScene()));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ROAD_GATE_TO_LEAGUE)
		|| a->getCollisionBitmask() == Model::BITMASK_ROAD_GATE_TO_LEAGUE && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, League::createScene()));
	}
	return true;

}

void Road::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/Road.tmx");
	auto m_objectGroup = map->getObjectGroup("Object");
	auto objects = m_objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++) {
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == Model::MODLE_TYPE_MAIN_CHARACTER) {
			mPlayer = new Trainer(this);
			mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
			roadBody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			roadBody->setCollisionBitmask(Model::BITMASK_PLAYER);
			roadBody->setContactTestBitmask(true);
			roadBody->setDynamic(true);
			roadBody->setRotationEnable(false);
			roadBody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(roadBody);
		}
		else if (type == Model::MODLE_TYPE_ROAD_GATE_TO_ROUTE2)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			roadGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			roadGateWay->setCollisionBitmask(Model::BITMASK_ROAD_GATE_TO_ROUTE2);
			roadGateWay->setContactTestBitmask(true);
			roadGateWay->setDynamic(false);
			roadGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(roadGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_ROAD_GATE_TO_LEAGUE)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			roadGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			roadGateWay->setCollisionBitmask(Model::BITMASK_ROAD_GATE_TO_LEAGUE);
			roadGateWay->setContactTestBitmask(true);
			roadGateWay->setDynamic(false);
			roadGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(roadGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}
}

void Road::UpdateCamera() {
	if (roadVisibleSize.width >= roadTileMapSize.width) {
		if (roadVisibleSize.height >= roadTileMapSize.height) {
			roadCamera->setPosition(roadTileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - roadTileMapSize.height / 2)>abs(roadTileMapSize.height / 2 - roadVisibleSize.height / 2)) {
				roadCamera->setPosition(roadTileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >roadCamera->getPosition().y) ? (roadTileMapSize.height - roadVisibleSize.height / 2) : roadVisibleSize.height / 2);
			}
			else {
				roadCamera->setPosition(roadTileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (roadVisibleSize.height >= roadTileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - roadTileMapSize.width / 2)>abs(roadTileMapSize.width / 2 - roadVisibleSize.width / 2)) {
				roadCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >roadCamera->getPosition().y) ? (roadTileMapSize.width - roadVisibleSize.width / 2) : roadVisibleSize.width / 2, roadTileMapSize.height / 2);
			}
			else {
				roadCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, roadTileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - roadTileMapSize.width / 2)>abs(roadTileMapSize.width / 2 - roadVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - roadTileMapSize.height / 2)>abs(roadTileMapSize.height / 2 - roadVisibleSize.height / 2)) {
				roadCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >roadCamera->getPosition().x) ? (roadTileMapSize.width - roadVisibleSize.width / 2) : roadVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >roadCamera->getPosition().y) ? (roadTileMapSize.height - roadVisibleSize.height / 2) : roadVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - roadTileMapSize.width / 2)>abs(roadTileMapSize.width / 2 - roadVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - roadTileMapSize.height / 2)<abs(roadTileMapSize.height / 2 - roadVisibleSize.height / 2)) {
				roadCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >roadCamera->getPosition().x) ? (roadTileMapSize.width - roadVisibleSize.width / 2) : roadVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - roadTileMapSize.width / 2)<abs(roadTileMapSize.width / 2 - roadVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - roadTileMapSize.height / 2)>abs(roadTileMapSize.height / 2 - roadVisibleSize.height / 2)) {
				roadCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >roadCamera->getPosition().y) ? (roadTileMapSize.height - roadVisibleSize.height / 2) : roadVisibleSize.height / 2);
			}
			else {
				roadCamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}

void Road::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(roadCamera->getPosition().x - 200, roadCamera->getPosition().y - 100);
}

