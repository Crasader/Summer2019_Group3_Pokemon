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
#include <cstdlib>

using namespace CocosDenshion;
USING_NS_CC;
Size cityVisibleSize;
Size cityTileMapSize;

PhysicsBody* cityBody, *cityGateWay;
Camera *cityCamera;
int City::previousScene = 0;


Scene* City::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = City::create();
	scene->addChild(layer);
	cityCamera = scene->getDefaultCamera();
	return scene;
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
				physics->setCollisionBitmask(13);
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				physics->setGravityEnable(false);
				physics->setMass(12);
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
	contactListener->onContactBegin = CC_CALLBACK_1(City::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
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
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_PC)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_PC && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_PC_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PokemonCenter::createScene()));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_CAVE)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_CAVE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_CAVE_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Cave::createScene()));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_LAKE)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_LAKE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_LAKE_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Lake::createScene()));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_ROUTE2)
		|| (a->getCollisionBitmask() == Model::BITMASK_CITY_GATE_TO_ROUTE2 && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		City::previousScene = Model::PRESCENE_ROUTE2_TO_CITY;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route2::createScene()));
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
void City::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(cityCamera->getPosition().x - 200, cityCamera->getPosition().y - 100);
}