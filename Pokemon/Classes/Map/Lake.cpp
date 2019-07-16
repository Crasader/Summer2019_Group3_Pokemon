
#include "Lake.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Pokemon\Charmander.h"
#include "Pokemon\Squirtle.h"
#include "Buttons.h"
#include "PokemonCenter.h"

USING_NS_CC;
Size visibleSize;
Size tileMapSize;

PhysicsBody* body, *gateWay;
Camera *camera;



Scene* Lake::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Lake::create();
	scene->addChild(layer);
	camera = scene->getDefaultCamera();
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

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/lake.tmx");
	tileMapSize = map->getContentSize();
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
				auto physics = PhysicsBody::createBox(tileSet->getContentSize()*2, PHYSICSBODY_MATERIAL_DEFAULT);
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
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, PokemonCenter::createScene()));
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
			body = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			body->setCollisionBitmask(17);
			body->setMass(16);
			body->setContactTestBitmask(true);
			body->setDynamic(true);
			body->setRotationEnable(false);
			body->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(body);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			gateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			gateWay->setCollisionBitmask(15);
			gateWay->setMass(14);
			gateWay->setContactTestBitmask(true);
			gateWay->setDynamic(false);
			gateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(gateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Lake:: updateCamera() {
	if (visibleSize.width >= tileMapSize.width) {
		if (visibleSize.height >= tileMapSize.height) {
			camera->setPosition(tileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - tileMapSize.height / 2)>abs(tileMapSize.height / 2 - visibleSize.height / 2)) {
				camera->setPosition(tileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >camera->getPosition().y)? (tileMapSize.height - visibleSize.height/2): visibleSize.height / 2);
			}
			else {
				camera->setPosition(tileMapSize.width / 2,mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (visibleSize.height >= tileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - tileMapSize.width / 2)>abs(tileMapSize.width / 2 - visibleSize.width / 2)) {
				camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >camera->getPosition().y) ? (tileMapSize.width - visibleSize.width / 2) : visibleSize.width / 2,tileMapSize.height / 2);
			}
			else {
				camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x , tileMapSize.height / 2 );
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - tileMapSize.width / 2)>abs(tileMapSize.width / 2 - visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - tileMapSize.height / 2)>abs(tileMapSize.height / 2 - visibleSize.height / 2)) {
				camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >camera->getPosition().x) ? (tileMapSize.width - visibleSize.width / 2) : visibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >camera->getPosition().y) ? (tileMapSize.height - visibleSize.height / 2) : visibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - tileMapSize.width / 2)>abs(tileMapSize.width / 2 - visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - tileMapSize.height / 2)<abs(tileMapSize.height / 2 - visibleSize.height / 2)) {
				camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >camera->getPosition().x) ? (tileMapSize.width - visibleSize.width / 2) : visibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y );
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - tileMapSize.width / 2)<abs(tileMapSize.width / 2 - visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - tileMapSize.height / 2)>abs(tileMapSize.height / 2 - visibleSize.height / 2)) {
				camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >camera->getPosition().y) ? (tileMapSize.height - visibleSize.height / 2) : visibleSize.height / 2 );
			}
			else {
				camera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}
	
}


float total = 0;

void Lake::update(float dt) {
	updateCamera();
	Buttons::getIntance()->UpdateButton(camera->getPosition().x - 200, camera->getPosition().y - 100);
}