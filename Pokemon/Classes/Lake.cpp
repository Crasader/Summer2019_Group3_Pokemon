
#include "Lake.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Pokemon\Charmander.h"
#include "Pokemon\Squirtle.h"
#include "Buttons.h"
#include "Model.h"

USING_NS_CC;
Size visibleSize;
Size tileMapSize;

PhysicsBody* body, *gateWay;
Camera *camera;

Button *up;
Button *down;
Button *left1;
Button *right1;

Scene* Lake::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Lake::create();
	scene->addChild(layer);
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
	
	camera = Camera::create();
	camera->setPosition(visibleSize/2);
	addChild(camera);

	CreateButon();
	ButtonListener();
	
	scheduleUpdate();
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

void Lake::CreateButon()
{
	up = Buttons::getIntance()->GetButtonUp();
	up->removeFromParent();

	right1 = Buttons::getIntance()->GetButtonRight();
	right1->removeFromParent();

	left1 = Buttons::getIntance()->GetButtonLeft();
	left1->removeFromParent();

	down = Buttons::getIntance()->GetButtonDown();
	down->removeFromParent();

	addChild(up, 100);
	addChild(right1, 100);
	addChild(left1, 100);
	addChild(down, 100);
}

void Lake::ButtonListener()
{
	up->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			this->mPlayer->walkUp();
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			this->mPlayer->GetSpriteFront()->stopActionByTag(0);
			//this->mPlayer->SetSprite(102);
			this->mPlayer->GetSpriteFront()->setTexture("res/Trainer/1.png");
			break;
		}
		default:
		{
			this->mPlayer->GetSpriteFront()->stopActionByTag(0);
			break;
		}
		}
	});


	right1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			this->mPlayer->walkRight();
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			this->mPlayer->GetSpriteFront()->stopActionByTag(3);
			break;
		}
		default:
		{
			this->mPlayer->GetSpriteFront()->stopActionByTag(3);
			break;
		}

		}
	});
	left1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			this->mPlayer->walkLeft();
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			this->mPlayer->GetSpriteFront()->stopActionByTag(2);
			//mPlayer->GetSprite()  = ResourceManager::GetInstance()->GetSpriteById(104);
			break;
		}
		default:
		{
			this->mPlayer->GetSpriteFront()->stopActionByTag(2);
			break;
		}
		}
	});
	down->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			this->mPlayer->walkDown();
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			this->mPlayer->GetSpriteFront()->stopActionByTag(1);
			break;
		}
		default:
		{
			this->mPlayer->GetSpriteFront()->stopActionByTag(1);
			break;
		}

		}
	});
}

float total = 0;

void Lake::update(float dt) {
	//auto followTheSprite = Follow::create(mPlayer->GetSprite(), Rect::ZERO);
	//this->runAction(followTheSprite);
}