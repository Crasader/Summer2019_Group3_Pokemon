
#include "Lab.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "Town.h"

USING_NS_CC;
Size LabvisibleSize;
Size LabtileMapSize;
PhysicsBody* Labbody, *LabgateWay;
Camera *Labcamera;



Scene* Lab::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Lab::create();
	scene->addChild(layer);
	Labcamera = scene->getDefaultCamera();
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Lab::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	LabvisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/tiensimap.tmx");
	LabtileMapSize = map->getContentSize();
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


	Button *up = Buttons::getIntance()->GetButtonUp();
	Button *right = Buttons::getIntance()->GetButtonRight();
	Button *left = Buttons::getIntance()->GetButtonLeft();
	Button *down = Buttons::getIntance()->GetButtonDown();
	up->retain();
	up->removeFromParent();
	up->release();
	right->retain();
	right->removeFromParent();
	right->release();
	left->retain();
	left->removeFromParent();
	left->release();
	down->retain();
	down->removeFromParent();
	down->release();
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);


	Buttons::getIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Lab::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Lab::onContactBegin(PhysicsContact& contact)

{

	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Town::createScene()));
	}

	return true;

}

void Lab::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/tiensimap.tmx");
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
			Labbody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Labbody->setCollisionBitmask(17);
			Labbody->setMass(16);
			Labbody->setContactTestBitmask(true);
			Labbody->setDynamic(true);
			Labbody->setRotationEnable(false);
			Labbody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(Labbody);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			LabgateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			LabgateWay->setCollisionBitmask(15);
			LabgateWay->setMass(14);
			LabgateWay->setContactTestBitmask(true);
			LabgateWay->setDynamic(false);
			LabgateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(LabgateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Lab::updateCamera() {
	if (LabvisibleSize.width >= LabtileMapSize.width) {
		if (LabvisibleSize.height >= LabtileMapSize.height) {
			Labcamera->setPosition(LabtileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - LabtileMapSize.height / 2)>abs(LabtileMapSize.height / 2 - LabvisibleSize.height / 2)) {
				Labcamera->setPosition(LabtileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Labcamera->getPosition().y) ? (LabtileMapSize.height - LabvisibleSize.height / 2) : LabvisibleSize.height / 2);
			}
			else {
				Labcamera->setPosition(LabtileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (LabvisibleSize.height >= LabtileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - LabtileMapSize.width / 2)>abs(LabtileMapSize.width / 2 - LabvisibleSize.width / 2)) {
				Labcamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Labcamera->getPosition().y) ? (LabtileMapSize.width - LabvisibleSize.width / 2) : LabvisibleSize.width / 2, LabtileMapSize.height / 2);
			}
			else {
				Labcamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, LabtileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - LabtileMapSize.width / 2)>abs(LabtileMapSize.width / 2 - LabvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - LabtileMapSize.height / 2)>abs(LabtileMapSize.height / 2 - LabvisibleSize.height / 2)) {
				Labcamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Labcamera->getPosition().x) ? (LabtileMapSize.width - LabvisibleSize.width / 2) : LabvisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Labcamera->getPosition().y) ? (LabtileMapSize.height - LabvisibleSize.height / 2) : LabvisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - LabtileMapSize.width / 2)>abs(LabtileMapSize.width / 2 - LabvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - LabtileMapSize.height / 2)<abs(LabtileMapSize.height / 2 - LabvisibleSize.height / 2)) {
				Labcamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Labcamera->getPosition().x) ? (LabtileMapSize.width - LabvisibleSize.width / 2) : LabvisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - LabtileMapSize.width / 2)<abs(LabtileMapSize.width / 2 - LabvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - LabtileMapSize.height / 2)>abs(LabtileMapSize.height / 2 - LabvisibleSize.height / 2)) {
				Labcamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Labcamera->getPosition().y) ? (LabtileMapSize.height - LabvisibleSize.height / 2) : LabvisibleSize.height / 2);
			}
			else {
				Labcamera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}

}
void Lab::update(float dt) {
	updateCamera();
	Buttons::getIntance()->UpdateButton(Labcamera->getPosition().x - 200, Labcamera->getPosition().y - 100);
}