
#include "Route1.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "Town.h"
#include "Lake.h"

USING_NS_CC;
Size Route1visibleSize;
Size Route1tileMapSize;

PhysicsBody* Route1body, *Route1gateWay;
Camera *Route1camera;



Scene* Route1::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Route1::create();
	scene->addChild(layer);
	Route1camera = scene->getDefaultCamera();
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
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Route1visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/route1.tmx");
	Route1tileMapSize = map->getContentSize();
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

	auto grass = map->getLayer("co");
	int count = 0;
	Size layerSize2 = grass->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize2.height; j++)
		{
			auto tilePokemon = grass->getTileAt(Vec2(i, j));
			if (tilePokemon != NULL)
			{
				if (count < 5) {
					int _random = rand() % 4;
					if (!_random) {
						auto pokemon = PhysicsBody::createBox(tilePokemon->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
						pokemon->setCollisionBitmask(12);
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

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Town::createScene()));
	}
	else if (a->getCollisionBitmask() == 19 && b->getCollisionBitmask() == 15
		|| a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 19)
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Lake::createScene()));
	}

	return true;

}

void Route1::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/route1.tmx");
	auto m_objectGroup = map->getObjectGroup("Object");
	auto objects = m_objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++) {
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == 1) {
			mPlayer = new Trainer(this);
			mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
			Route1body = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Route1body->setCollisionBitmask(15);
			Route1body->setMass(14);
			Route1body->setContactTestBitmask(true);
			Route1body->setDynamic(true);
			Route1body->setRotationEnable(false);
			Route1body->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(Route1body);
		}
		else if (type ==2)
			{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			Route1gateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Route1gateWay->setCollisionBitmask(17);
			Route1gateWay->setMass(16);
			Route1gateWay->setContactTestBitmask(true);
			Route1gateWay->setDynamic(false);
			Route1gateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(Route1gateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type==3)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			Route1gateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Route1gateWay->setCollisionBitmask(19);
			Route1gateWay->setMass(18);
			Route1gateWay->setContactTestBitmask(true);
			Route1gateWay->setDynamic(false);
			Route1gateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(Route1gateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Route1::updateCamera() {
	if (Route1visibleSize.width >= Route1tileMapSize.width) {
		if (Route1visibleSize.height >= Route1tileMapSize.height) {
			Route1camera->setPosition(Route1tileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - Route1tileMapSize.height / 2)>abs(Route1tileMapSize.height / 2 - Route1visibleSize.height / 2)) {
				Route1camera->setPosition(Route1tileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Route1camera->getPosition().y) ? (Route1tileMapSize.height - Route1visibleSize.height / 2) : Route1visibleSize.height / 2);
			}
			else {
				Route1camera->setPosition(Route1tileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (Route1visibleSize.height >= Route1tileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - Route1tileMapSize.width / 2)>abs(Route1tileMapSize.width / 2 - Route1visibleSize.width / 2)) {
				Route1camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Route1camera->getPosition().y) ? (Route1tileMapSize.width - Route1visibleSize.width / 2) : Route1visibleSize.width / 2, Route1tileMapSize.height / 2);
			}
			else {
				Route1camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, Route1tileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - Route1tileMapSize.width / 2)>abs(Route1tileMapSize.width / 2 - Route1visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - Route1tileMapSize.height / 2)>abs(Route1tileMapSize.height / 2 - Route1visibleSize.height / 2)) {
				Route1camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Route1camera->getPosition().x) ? (Route1tileMapSize.width - Route1visibleSize.width / 2) : Route1visibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Route1camera->getPosition().y) ? (Route1tileMapSize.height - Route1visibleSize.height / 2) : Route1visibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - Route1tileMapSize.width / 2)>abs(Route1tileMapSize.width / 2 - Route1visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - Route1tileMapSize.height / 2)<abs(Route1tileMapSize.height / 2 - Route1visibleSize.height / 2)) {
				Route1camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Route1camera->getPosition().x) ? (Route1tileMapSize.width - Route1visibleSize.width / 2) : Route1visibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - Route1tileMapSize.width / 2)<abs(Route1tileMapSize.width / 2 - Route1visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - Route1tileMapSize.height / 2)>abs(Route1tileMapSize.height / 2 - Route1visibleSize.height / 2)) {
				Route1camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Route1camera->getPosition().y) ? (Route1tileMapSize.height - Route1visibleSize.height / 2) : Route1visibleSize.height / 2);
			}
			else {
				Route1camera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}

}
void Route1::update(float dt) {
	updateCamera();
	Buttons::GetIntance()->UpdateButton(Route1camera->getPosition().x - 200, Route1camera->getPosition().y - 100);
}
