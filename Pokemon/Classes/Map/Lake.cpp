#include "Lake.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "City.h"
#include "Model.h"

USING_NS_CC;
Size lakevisibleSize;
Size laketileMapSize;

PhysicsBody* lakebody, *lakegateWay;
Camera *lakecamera;



Scene* Lake::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Lake::create();
	scene->addChild(layer);
	lakecamera = scene->getDefaultCamera();
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

	lakevisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/Lake.tmx");
	laketileMapSize = map->getContentSize();
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
	contactListener->onContactBegin = CC_CALLBACK_1(Lake::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
    return true;
}

bool Lake::onContactBegin(PhysicsContact& contact)

{

	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_LAKE_GATE)
		|| (a->getCollisionBitmask() == Model::BITMASK_LAKE_GATE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, City::createScene()));
	}

	return true;

}

void Lake::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/Lake.tmx");
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
			lakebody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			lakebody->setCollisionBitmask(Model::BITMASK_PLAYER);
			lakebody->setContactTestBitmask(true);
			lakebody->setDynamic(true);
			lakebody->setRotationEnable(false);
			lakebody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(lakebody);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			lakegateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			lakegateWay->setCollisionBitmask(Model::BITMASK_LAKE_GATE);
			lakegateWay->setContactTestBitmask(true);
			lakegateWay->setDynamic(false);
			lakegateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(lakegateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Lake::UpdateCamera() {
	if (lakevisibleSize.width >= laketileMapSize.width) {
		if (lakevisibleSize.height >= laketileMapSize.height) {
			lakecamera->setPosition(laketileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - laketileMapSize.height / 2)>abs(laketileMapSize.height / 2 - lakevisibleSize.height / 2)) {
				lakecamera->setPosition(laketileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >lakecamera->getPosition().y) ? (laketileMapSize.height - lakevisibleSize.height / 2) : lakevisibleSize.height / 2);
			}
			else {
				lakecamera->setPosition(laketileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (lakevisibleSize.height >= laketileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - laketileMapSize.width / 2)>abs(laketileMapSize.width / 2 - lakevisibleSize.width / 2)) {
				lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >lakecamera->getPosition().y) ? (laketileMapSize.width - lakevisibleSize.width / 2) : lakevisibleSize.width / 2, laketileMapSize.height / 2);
			}
			else {
				lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, laketileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - laketileMapSize.width / 2)>abs(laketileMapSize.width / 2 - lakevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - laketileMapSize.height / 2)>abs(laketileMapSize.height / 2 - lakevisibleSize.height / 2)) {
				lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >lakecamera->getPosition().x) ? (laketileMapSize.width - lakevisibleSize.width / 2) : lakevisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >lakecamera->getPosition().y) ? (laketileMapSize.height - lakevisibleSize.height / 2) : lakevisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - laketileMapSize.width / 2)>abs(laketileMapSize.width / 2 - lakevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - laketileMapSize.height / 2)<abs(laketileMapSize.height / 2 - lakevisibleSize.height / 2)) {
				lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >lakecamera->getPosition().x) ? (laketileMapSize.width - lakevisibleSize.width / 2) : lakevisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - laketileMapSize.width / 2)<abs(laketileMapSize.width / 2 - lakevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - laketileMapSize.height / 2)>abs(laketileMapSize.height / 2 - lakevisibleSize.height / 2)) {
				lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >lakecamera->getPosition().y) ? (laketileMapSize.height - lakevisibleSize.height / 2) : lakevisibleSize.height / 2);
			}
			else {
				lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}
void Lake::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(lakecamera->getPosition().x - 200, lakecamera->getPosition().y - 100);
}