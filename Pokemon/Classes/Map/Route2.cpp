
#include "Route2.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "City.h"
#include "Victoryroad.h"

USING_NS_CC;
Size Route2visibleSize;
Size Route2tileMapSize;

PhysicsBody* Route2body, *Route2gateWay;
Camera *Route2camera;
int Route2::previousScene = 0;


Scene* Route2::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Route2::create();
	scene->addChild(layer);
	Route2camera = scene->getDefaultCamera();
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Route2::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Route2visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/Route2.tmx");
	Route2tileMapSize = map->getContentSize();
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
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);


	Buttons::getIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Route2::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Route2::onContactBegin(PhysicsContact& contact)

{

	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
		Director::getInstance()->getRunningScene()->pause();
		City::previousScene = 4;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, City::createScene()));
	}
	else if (a->getCollisionBitmask() == 19 && b->getCollisionBitmask() == 15
		|| a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 19)
	{
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Road::createScene()));
	}

	return true;

}

void Route2::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/Route2.tmx");
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
				Route2body = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				Route2body->setCollisionBitmask(15);
				Route2body->setMass(14);
				Route2body->setContactTestBitmask(true);
				Route2body->setDynamic(true);
				Route2body->setRotationEnable(false);
				Route2body->setGravityEnable(false);
				mPlayer->GetSpriteFront()->setPhysicsBody(Route2body);
			}
			else continue;
		}
		else if (type == 2)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			Route2gateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Route2gateWay->setCollisionBitmask(17);
			Route2gateWay->setMass(16);
			Route2gateWay->setContactTestBitmask(true);
			Route2gateWay->setDynamic(false);
			Route2gateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(Route2gateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == 3)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			Route2gateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Route2gateWay->setCollisionBitmask(19);
			Route2gateWay->setMass(18);
			Route2gateWay->setContactTestBitmask(true);
			Route2gateWay->setDynamic(false);
			Route2gateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(Route2gateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Route2::updateCamera() {
	if (Route2visibleSize.width >= Route2tileMapSize.width) {
		if (Route2visibleSize.height >= Route2tileMapSize.height) {
			Route2camera->setPosition(Route2tileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - Route2tileMapSize.height / 2)>abs(Route2tileMapSize.height / 2 - Route2visibleSize.height / 2)) {
				Route2camera->setPosition(Route2tileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Route2camera->getPosition().y) ? (Route2tileMapSize.height - Route2visibleSize.height / 2) : Route2visibleSize.height / 2);
			}
			else {
				Route2camera->setPosition(Route2tileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (Route2visibleSize.height >= Route2tileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - Route2tileMapSize.width / 2)>abs(Route2tileMapSize.width / 2 - Route2visibleSize.width / 2)) {
				Route2camera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Route2camera->getPosition().y) ? (Route2tileMapSize.width - Route2visibleSize.width / 2) : Route2visibleSize.width / 2, Route2tileMapSize.height / 2);
			}
			else {
				Route2camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, Route2tileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - Route2tileMapSize.width / 2)>abs(Route2tileMapSize.width / 2 - Route2visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - Route2tileMapSize.height / 2)>abs(Route2tileMapSize.height / 2 - Route2visibleSize.height / 2)) {
				Route2camera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >Route2camera->getPosition().x) ? (Route2tileMapSize.width - Route2visibleSize.width / 2) : Route2visibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Route2camera->getPosition().y) ? (Route2tileMapSize.height - Route2visibleSize.height / 2) : Route2visibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - Route2tileMapSize.width / 2)>abs(Route2tileMapSize.width / 2 - Route2visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - Route2tileMapSize.height / 2)<abs(Route2tileMapSize.height / 2 - Route2visibleSize.height / 2)) {
				Route2camera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >Route2camera->getPosition().x) ? (Route2tileMapSize.width - Route2visibleSize.width / 2) : Route2visibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - Route2tileMapSize.width / 2)<abs(Route2tileMapSize.width / 2 - Route2visibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - Route2tileMapSize.height / 2)>abs(Route2tileMapSize.height / 2 - Route2visibleSize.height / 2)) {
				Route2camera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Route2camera->getPosition().y) ? (Route2tileMapSize.height - Route2visibleSize.height / 2) : Route2visibleSize.height / 2);
			}
			else {
				Route2camera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}

}
void Route2::update(float dt) {
	updateCamera();
	Buttons::getIntance()->UpdateButton(Route2camera->getPosition().x - 200, Route2camera->getPosition().y - 100);
}