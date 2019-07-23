
#include "Lake.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
<<<<<<< HEAD
#include "Buttons.h"
#include "City.h"
=======
#include "ResourceManager.h"
#include "Buttons.h"
#include "Route1.h"
>>>>>>> master

USING_NS_CC;
Size LakevisibleSize;
Size LaketileMapSize;

PhysicsBody* Lakebody, *LakegateWay;
Camera *Lakecamera;



Scene* Lake::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Lake::create();
	scene->addChild(layer);
	Lakecamera = scene->getDefaultCamera();
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Lake::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	LakevisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/lake.tmx");
	LaketileMapSize = map->getContentSize();
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

<<<<<<< HEAD
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
				if (count < 5) {
					int rand = random() % 4;
					if (!rand) {
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
=======
	InitObject();
	

	Button *up = Buttons::GetIntance()->GetButtonUp();
	Button *right = Buttons::GetIntance()->GetButtonRight();
	Button *left = Buttons::GetIntance()->GetButtonLeft();
	Button *down = Buttons::GetIntance()->GetButtonDown();
>>>>>>> master
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);


<<<<<<< HEAD
	Buttons::getIntance()->ButtonListener(this->mPlayer);
=======
	Buttons::GetIntance()->ButtonListener(this->mPlayer);
>>>>>>> master
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Lake::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
    return true;
}

bool Lake::onContactBegin(PhysicsContact& contact)

{

	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
<<<<<<< HEAD
		Director::getInstance()->getRunningScene()->pause();
		City::previousScene = 3;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, City::createScene()));
=======
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route1::createScene()));
>>>>>>> master
	}

	return true;

}

void Lake::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/lake.tmx");
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
			Lakebody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Lakebody->setCollisionBitmask(17);
			Lakebody->setMass(16);
			Lakebody->setContactTestBitmask(true);
			Lakebody->setDynamic(true);
			Lakebody->setRotationEnable(false);
			Lakebody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(Lakebody);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			LakegateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			LakegateWay->setCollisionBitmask(15);
			LakegateWay->setMass(14);
			LakegateWay->setContactTestBitmask(true);
			LakegateWay->setDynamic(false);
			LakegateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(LakegateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

<<<<<<< HEAD
void Lake::updateCamera() {
=======
void Lake:: updateCamera() {
>>>>>>> master
	if (LakevisibleSize.width >= LaketileMapSize.width) {
		if (LakevisibleSize.height >= LaketileMapSize.height) {
			Lakecamera->setPosition(LaketileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - LaketileMapSize.height / 2)>abs(LaketileMapSize.height / 2 - LakevisibleSize.height / 2)) {
<<<<<<< HEAD
				Lakecamera->setPosition(LaketileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().y) ? (LaketileMapSize.height - LakevisibleSize.height / 2) : LakevisibleSize.height / 2);
			}
			else {
				Lakecamera->setPosition(LaketileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
=======
				Lakecamera->setPosition(LaketileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().y)? (LaketileMapSize.height - LakevisibleSize.height/2): LakevisibleSize.height / 2);
			}
			else {
				Lakecamera->setPosition(LaketileMapSize.width / 2,mPlayer->GetSpriteFront()->getPosition().y);
>>>>>>> master
			}
		}
	}
	else {
		if (LakevisibleSize.height >= LaketileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - LaketileMapSize.width / 2)>abs(LaketileMapSize.width / 2 - LakevisibleSize.width / 2)) {
				Lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().y) ? (LaketileMapSize.width - LakevisibleSize.width / 2) : LakevisibleSize.width / 2, LaketileMapSize.height / 2);
			}
			else {
<<<<<<< HEAD
				Lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, LaketileMapSize.height / 2);
=======
				Lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x , LaketileMapSize.height / 2 );
>>>>>>> master
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - LaketileMapSize.width / 2)>abs(LaketileMapSize.width / 2 - LakevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - LaketileMapSize.height / 2)>abs(LaketileMapSize.height / 2 - LakevisibleSize.height / 2)) {
<<<<<<< HEAD
				Lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >Lakecamera->getPosition().x) ? (LaketileMapSize.width - LakevisibleSize.width / 2) : LakevisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().y) ? (LaketileMapSize.height - LakevisibleSize.height / 2) : LakevisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - LaketileMapSize.width / 2)>abs(LaketileMapSize.width / 2 - LakevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - LaketileMapSize.height / 2)<abs(LaketileMapSize.height / 2 - LakevisibleSize.height / 2)) {
				Lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >Lakecamera->getPosition().x) ? (LaketileMapSize.width - LakevisibleSize.width / 2) : LakevisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - LaketileMapSize.width / 2)<abs(LaketileMapSize.width / 2 - LakevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - LaketileMapSize.height / 2)>abs(LaketileMapSize.height / 2 - LakevisibleSize.height / 2)) {
				Lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().y) ? (LaketileMapSize.height - LakevisibleSize.height / 2) : LakevisibleSize.height / 2);
			}
			else {
				Lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}

}
void Lake::update(float dt) {
	updateCamera();
	Buttons::getIntance()->UpdateButton(Lakecamera->getPosition().x - 200, Lakecamera->getPosition().y - 100);
=======
				Lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().x) ? (LaketileMapSize.width - LakevisibleSize.width / 2) : LakevisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().y) ? (LaketileMapSize.height - LakevisibleSize.height / 2) : LakevisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - LaketileMapSize.width / 2)>abs(LaketileMapSize.width / 2 - LakevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - LaketileMapSize.height / 2)<abs(LaketileMapSize.height / 2 - LakevisibleSize.height / 2)) {
				Lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().x) ? (LaketileMapSize.width - LakevisibleSize.width / 2) : LakevisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y );
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - LaketileMapSize.width / 2)<abs(LaketileMapSize.width / 2 - LakevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - LaketileMapSize.height / 2)>abs(LaketileMapSize.height / 2 - LakevisibleSize.height / 2)) {
				Lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Lakecamera->getPosition().y) ? (LaketileMapSize.height - LakevisibleSize.height / 2) : LakevisibleSize.height / 2 );
			}
			else {
				Lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}
	
}
void Lake::update(float dt) {
	updateCamera();
	Buttons::GetIntance()->UpdateButton(Lakecamera->getPosition().x - 200, Lakecamera->getPosition().y - 100);
>>>>>>> master
}