#include "Cave.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "City.h"
USING_NS_CC;

Size CavevisibleSize;
Size CavetileMapSize;

PhysicsBody* Cavebody, *CavegateWay;
Camera *Cavecamera;

Scene * Cave::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Cave::create();
	scene->addChild(layer);
	Cavecamera = scene->getDefaultCamera();
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Cave::init()
{
	if (!Layer::init())
	{
		return false;
	}

	CavevisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/untitled.tmx");
	CavetileMapSize = map->getContentSize();
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
	contactListener->onContactBegin = CC_CALLBACK_1(Cave::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Cave::onContactBegin(PhysicsContact & contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
		Director::getInstance()->getRunningScene()->pause();
		City::previousScene = 2;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, City::createScene()));
	}

	return true;

}

void Cave::InitObject()
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
			Cavebody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Cavebody->setCollisionBitmask(17);
			Cavebody->setMass(16);
			Cavebody->setContactTestBitmask(true);
			Cavebody->setDynamic(true);
			Cavebody->setRotationEnable(false);
			Cavebody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(Cavebody);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			CavegateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			CavegateWay->setCollisionBitmask(15);
			CavegateWay->setMass(14);
			CavegateWay->setContactTestBitmask(true);
			CavegateWay->setDynamic(false);
			CavegateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(CavegateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Cave::updateCamera() {
	if (CavevisibleSize.width >= CavetileMapSize.width) {
		if (CavevisibleSize.height >= CavetileMapSize.height) {
			Cavecamera->setPosition(CavetileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - CavetileMapSize.height / 2)>abs(CavetileMapSize.height / 2 - CavevisibleSize.height / 2)) {
				Cavecamera->setPosition(CavetileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Cavecamera->getPosition().y) ? (CavetileMapSize.height - CavevisibleSize.height / 2) : CavevisibleSize.height / 2);
			}
			else {
				Cavecamera->setPosition(CavetileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (CavevisibleSize.height >= CavetileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - CavetileMapSize.width / 2)>abs(CavetileMapSize.width / 2 - CavevisibleSize.width / 2)) {
				Cavecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Cavecamera->getPosition().y) ? (CavetileMapSize.width - CavevisibleSize.width / 2) : CavevisibleSize.width / 2, CavetileMapSize.height / 2);
			}
			else {
				Cavecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, CavetileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - CavetileMapSize.width / 2)>abs(CavetileMapSize.width / 2 - CavevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - CavetileMapSize.height / 2)>abs(CavetileMapSize.height / 2 - CavevisibleSize.height / 2)) {
				Cavecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >Cavecamera->getPosition().x) ? (CavetileMapSize.width - CavevisibleSize.width / 2) : CavevisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Cavecamera->getPosition().y) ? (CavetileMapSize.height - CavevisibleSize.height / 2) : CavevisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - CavetileMapSize.width / 2)>abs(CavetileMapSize.width / 2 - CavevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - CavetileMapSize.height / 2)<abs(CavetileMapSize.height / 2 - CavevisibleSize.height / 2)) {
				Cavecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >Cavecamera->getPosition().x) ? (CavetileMapSize.width - CavevisibleSize.width / 2) : CavevisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - CavetileMapSize.width / 2)<abs(CavetileMapSize.width / 2 - CavevisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - CavetileMapSize.height / 2)>abs(CavetileMapSize.height / 2 - CavevisibleSize.height / 2)) {
				Cavecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Cavecamera->getPosition().y) ? (CavetileMapSize.height - CavevisibleSize.height / 2) : CavevisibleSize.height / 2);
			}
			else {
				Cavecamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}

}

void Cave::update(float dt)
{
	updateCamera();
	Buttons::getIntance()->UpdateButton(Cavecamera->getPosition().x - 200, Cavecamera->getPosition().y - 100);
}
