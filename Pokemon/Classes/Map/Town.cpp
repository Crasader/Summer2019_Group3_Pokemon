
#include "Town.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "Lab.h"
#include "Route1.h"
#include "House.h"
#include "Model.h"
#include "Scene\BattleScene.h"
#include <cstdlib>

USING_NS_CC;
Size townVisibleSize;
Size townTileMapSize;

PhysicsBody* townBody, *townGateWay;
Camera *townCamera;
int Town::previousScene = 0;


Scene* Town::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Town::create();
	scene->addChild(layer);
	townCamera = scene->getDefaultCamera();
	return scene;
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Town::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	townVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto map = ResourceManager::GetInstance()->GetTiledMapById(2);
	townTileMapSize = map->getContentSize();
	addChild(map);
	auto mapHouse = ResourceManager::GetInstance()->GetTiledMapById(3);
	addChild(mapHouse, 15);
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
				physics->setMass(12);
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
				if (count < 3) {
					int _random = rand() % 4;
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
	contactListener->onContactBegin = CC_CALLBACK_1(Town::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Town::onContactBegin(PhysicsContact& contact)

{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_HOUSE)
		|| (a->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_HOUSE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		Town::previousScene = Model::PRESCENE_HOUSE_TO_TOWN;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, House::createScene()));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_LAB)
		|| (a->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_LAB && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		Town::previousScene = Model::PRESCENE_LAB_TO_TOWN;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Lab::createScene()));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_ROUTE1)
		|| (a->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_ROUTE1 && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		Town::previousScene = Model::PRESCENE_ROUTE1_TO_TOWN;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route1::createScene()));
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_POKEMON)
		|| (a->getCollisionBitmask() == Model::BITMASK_POKEMON && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		//int idPokemon = random();
		//new Pokemon with id
		//chuyen scene chien dau
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(BattleScene::createScene());
		CCLOG("Has Pokemon");
	}
	if ((a->getCollisionBitmask() == Model::BITMASK_WORLD && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WORLD))
	{
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

void Town::InitObject()
{
	auto map = ResourceManager::GetInstance()->GetTiledMapById(2);
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
				mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
				townBody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				townBody->setCollisionBitmask(Model::BITMASK_PLAYER);
				townBody->setContactTestBitmask(true);
				townBody->setDynamic(true);
				townBody->setRotationEnable(false);
				townBody->setGravityEnable(false);
				mPlayer->GetSpriteFront()->setPhysicsBody(townBody);
			}
			else continue;
		}
		else if (type == Model::MODLE_TYPE_TOWN_GATE_TO_HOUSE)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			townGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			townGateWay->setCollisionBitmask(Model::BITMASK_TOWN_GATE_TO_HOUSE);
			townGateWay->setContactTestBitmask(true);
			townGateWay->setDynamic(false);
			townGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(townGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_TOWN_GATE_TO_LAB)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			townGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			townGateWay->setCollisionBitmask(Model::BITMASK_TOWN_GATE_TO_LAB);
			townGateWay->setContactTestBitmask(true);
			townGateWay->setDynamic(false);
			townGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(townGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_TOWN_GATE_TO_ROUTE1)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			townGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			townGateWay->setCollisionBitmask(Model::BITMASK_TOWN_GATE_TO_ROUTE1);
			townGateWay->setContactTestBitmask(true);
			townGateWay->setDynamic(false);
			townGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(townGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Town::UpdateCamera() {
	if (townVisibleSize.width >= townTileMapSize.width) {
		if (townVisibleSize.height >= townTileMapSize.height) {
			townCamera->setPosition(townTileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - townTileMapSize.height / 2)>abs(townTileMapSize.height / 2 - townVisibleSize.height / 2)) {
				townCamera->setPosition(townTileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().y) ? (townTileMapSize.height - townVisibleSize.height / 2) : townVisibleSize.height / 2);
			}
			else {
				townCamera->setPosition(townTileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (townVisibleSize.height >= townTileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - townTileMapSize.width / 2)>abs(townTileMapSize.width / 2 - townVisibleSize.width / 2)) {
				townCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().y) ? (townTileMapSize.width - townVisibleSize.width / 2) : townVisibleSize.width / 2, townTileMapSize.height / 2);
			}
			else {
				townCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, townTileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - townTileMapSize.width / 2)>abs(townTileMapSize.width / 2 - townVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - townTileMapSize.height / 2)>abs(townTileMapSize.height / 2 - townVisibleSize.height / 2)) {
				townCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().x) ? (townTileMapSize.width - townVisibleSize.width / 2) : townVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().y) ? (townTileMapSize.height - townVisibleSize.height / 2) : townVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - townTileMapSize.width / 2)>abs(townTileMapSize.width / 2 - townVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - townTileMapSize.height / 2)<abs(townTileMapSize.height / 2 - townVisibleSize.height / 2)) {
				townCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().x) ? (townTileMapSize.width - townVisibleSize.width / 2) : townVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - townTileMapSize.width / 2)<abs(townTileMapSize.width / 2 - townVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - townTileMapSize.height / 2)>abs(townTileMapSize.height / 2 - townVisibleSize.height / 2)) {
				townCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().y) ? (townTileMapSize.height - townVisibleSize.height / 2) : townVisibleSize.height / 2);
			}
			else {
				townCamera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}

}
void Town::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(townCamera->getPosition().x - 200, townCamera->getPosition().y - 100);
}