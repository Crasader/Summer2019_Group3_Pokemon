#include "House.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "Map/PokemonCenter.h"
#include "Town.h"
USING_NS_CC;

Size HousevisibleSize;
Size HousetileMapSize;

PhysicsBody* Housebody, *HousegateWay;
Camera *Housecamera;

Scene * House::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = House::create();
	scene->addChild(layer);
	Housecamera = scene->getDefaultCamera();
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool House::init()
{
	if (!Layer::init())
	{
		return false;
	}

	HousevisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/untitled.tmx");
	HousetileMapSize = map->getContentSize();
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
	up->removeFromParent();
	right->removeFromParent();
	left->removeFromParent();
	down->removeFromParent();
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);


	Buttons::GetIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(House::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool House::onContactBegin(PhysicsContact & contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
		Director::getInstance()->getRunningScene()->pause();
		Town::previousScene = 0;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Town::createScene()));
	}

	return true;

}

void House::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/untitled.tmx");
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
			Housebody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Housebody->setCollisionBitmask(17);
			Housebody->setMass(16);
			Housebody->setContactTestBitmask(true);
			Housebody->setDynamic(true);
			Housebody->setRotationEnable(false);
			Housebody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(Housebody);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			HousegateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			HousegateWay->setCollisionBitmask(15);
			HousegateWay->setMass(14);
			HousegateWay->setContactTestBitmask(true);
			HousegateWay->setDynamic(false);
			HousegateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(HousegateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void House::updateCamera()
{
	if (HousevisibleSize.width >= HousetileMapSize.width) {
		if (HousevisibleSize.height >= HousetileMapSize.height) {
			Housecamera->setPosition(HousetileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - HousetileMapSize.height / 2)>abs(HousetileMapSize.height / 2 - HousevisibleSize.height / 2)) {
				Housecamera->setPosition(HousetileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Housecamera->getPosition().y) ? (HousetileMapSize.height - HousevisibleSize.height / 2) : HousevisibleSize.height / 2);
			}
			else {
				Housecamera->setPosition(HousetileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (HousevisibleSize.height >= HousetileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - HousetileMapSize.width / 2)>abs(HousetileMapSize.width / 2 - HousevisibleSize.width / 2)) {
				Housecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Housecamera->getPosition().y) ? (HousetileMapSize.width - HousevisibleSize.width / 2) : HousevisibleSize.width / 2, HousetileMapSize.height / 2);
			}
			else {
				Housecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, HousetileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - HousetileMapSize.width / 2)>abs(HousetileMapSize.width / 2 - HousevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - HousetileMapSize.height / 2)>abs(HousetileMapSize.height / 2 - HousevisibleSize.height / 2)) {
				Housecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Housecamera->getPosition().x) ? (HousetileMapSize.width - HousevisibleSize.width / 2) : HousevisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Housecamera->getPosition().y) ? (HousetileMapSize.height - HousevisibleSize.height / 2) : HousevisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - HousetileMapSize.width / 2)>abs(HousetileMapSize.width / 2 - HousevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - HousetileMapSize.height / 2)<abs(HousetileMapSize.height / 2 - HousevisibleSize.height / 2)) {
				Housecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Housecamera->getPosition().x) ? (HousetileMapSize.width - HousevisibleSize.width / 2) : HousevisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - HousetileMapSize.width / 2)<abs(HousetileMapSize.width / 2 - HousevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - HousetileMapSize.height / 2)>abs(HousetileMapSize.height / 2 - HousevisibleSize.height / 2)) {
				Housecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Housecamera->getPosition().y) ? (HousetileMapSize.height - HousevisibleSize.height / 2) : HousevisibleSize.height / 2);
			}
			else {
				Housecamera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}
}

void House::update(float dt)
{
	updateCamera();
	Buttons::GetIntance()->UpdateButton(Housecamera->getPosition().x - 200, Housecamera->getPosition().y - 100);
}
