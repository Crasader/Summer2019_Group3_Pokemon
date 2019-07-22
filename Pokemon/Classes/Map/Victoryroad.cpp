
#include "Victoryroad.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include"Route2.h"
#include "Championleague.h"

USING_NS_CC;
Size RoadvisibleSize;
Size RoadtileMapSize;

PhysicsBody* Roadbody, *RoadgateWay;
Camera *Roadcamera;
int Road::previousScene = 0;


Scene* Road::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Road::create();
	scene->addChild(layer);
	Roadcamera = scene->getDefaultCamera();
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
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	RoadvisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/Road.tmx");
	RoadtileMapSize = map->getContentSize();
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
	contactListener->onContactBegin = CC_CALLBACK_1(Road::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Road::onContactBegin(PhysicsContact& contact)

{

	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
		Director::getInstance()->getRunningScene()->pause();
		Route2::previousScene = 1;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route2::createScene()));
	}
	else if (a->getCollisionBitmask() == 19 && b->getCollisionBitmask() == 15
		|| a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 19)
	{
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
		if (type == 1) {
			int preScene = object.asValueMap().at("pre").asInt();
			if (preScene == previousScene) {
				mPlayer = new Trainer(this);
				if (preScene == 0)
				{
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkright/1.png");
				}
				else
				{
					mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkleft/1.png");
				}
				mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
				Roadbody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				Roadbody->setCollisionBitmask(15);
				Roadbody->setMass(14);
				Roadbody->setContactTestBitmask(true);
				Roadbody->setDynamic(true);
				Roadbody->setRotationEnable(false);
				Roadbody->setGravityEnable(false);
				mPlayer->GetSpriteFront()->setPhysicsBody(Roadbody);
			}
			else continue;
		}
		else if (type == 2)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			RoadgateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			RoadgateWay->setCollisionBitmask(17);
			RoadgateWay->setMass(16);
			RoadgateWay->setContactTestBitmask(true);
			RoadgateWay->setDynamic(false);
			RoadgateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(RoadgateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == 3)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			RoadgateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			RoadgateWay->setCollisionBitmask(19);
			RoadgateWay->setMass(18);
			RoadgateWay->setContactTestBitmask(true);
			RoadgateWay->setDynamic(false);
			RoadgateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(RoadgateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Road::updateCamera() {
	if (RoadvisibleSize.width >= RoadtileMapSize.width) {
		if (RoadvisibleSize.height >= RoadtileMapSize.height) {
			Roadcamera->setPosition(RoadtileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - RoadtileMapSize.height / 2)>abs(RoadtileMapSize.height / 2 - RoadvisibleSize.height / 2)) {
				Roadcamera->setPosition(RoadtileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Roadcamera->getPosition().y) ? (RoadtileMapSize.height - RoadvisibleSize.height / 2) : RoadvisibleSize.height / 2);
			}
			else {
				Roadcamera->setPosition(RoadtileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (RoadvisibleSize.height >= RoadtileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - RoadtileMapSize.width / 2)>abs(RoadtileMapSize.width / 2 - RoadvisibleSize.width / 2)) {
				Roadcamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Roadcamera->getPosition().y) ? (RoadtileMapSize.width - RoadvisibleSize.width / 2) : RoadvisibleSize.width / 2, RoadtileMapSize.height / 2);
			}
			else {
				Roadcamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, RoadtileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - RoadtileMapSize.width / 2)>abs(RoadtileMapSize.width / 2 - RoadvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - RoadtileMapSize.height / 2)>abs(RoadtileMapSize.height / 2 - RoadvisibleSize.height / 2)) {
				Roadcamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >Roadcamera->getPosition().x) ? (RoadtileMapSize.width - RoadvisibleSize.width / 2) : RoadvisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Roadcamera->getPosition().y) ? (RoadtileMapSize.height - RoadvisibleSize.height / 2) : RoadvisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - RoadtileMapSize.width / 2)>abs(RoadtileMapSize.width / 2 - RoadvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - RoadtileMapSize.height / 2)<abs(RoadtileMapSize.height / 2 - RoadvisibleSize.height / 2)) {
				Roadcamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >Roadcamera->getPosition().x) ? (RoadtileMapSize.width - RoadvisibleSize.width / 2) : RoadvisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - RoadtileMapSize.width / 2)<abs(RoadtileMapSize.width / 2 - RoadvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - RoadtileMapSize.height / 2)>abs(RoadtileMapSize.height / 2 - RoadvisibleSize.height / 2)) {
				Roadcamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Roadcamera->getPosition().y) ? (RoadtileMapSize.height - RoadvisibleSize.height / 2) : RoadvisibleSize.height / 2);
			}
			else {
				Roadcamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}

}
void Road::update(float dt) {
	updateCamera();
	Buttons::getIntance()->UpdateButton(Roadcamera->getPosition().x - 200, Roadcamera->getPosition().y - 100);
}