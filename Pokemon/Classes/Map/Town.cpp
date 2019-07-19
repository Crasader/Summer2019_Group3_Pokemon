
#include "Town.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "Lab.h"
#include "Route1.h"
#include "House.h"

USING_NS_CC;
Size TownvisibleSize;
Size TowntileMapSize;

PhysicsBody* Townbody, *TowngateWay;
Camera *Towncamera;
int Town::previousScene = 0;


Scene* Town::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Town::create();
	scene->addChild(layer);
	Towncamera = scene->getDefaultCamera();
	return scene;
}


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Town::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	TownvisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/Townmap1.tmx");
	TowntileMapSize = map->getContentSize();
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
				if (count < 3) {
					int rand = random()%4;
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
	contactListener->onContactBegin = CC_CALLBACK_1(Town::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Town::onContactBegin(PhysicsContact& contact)

{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, House::createScene()));
	}
	else if (a->getCollisionBitmask() == 19 && b->getCollisionBitmask() == 15
		|| a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 19)
	{
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Lab::createScene()));
	}
	else if (a->getCollisionBitmask() == 21 && b->getCollisionBitmask() == 15
		|| a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 21)
	{
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route1::createScene()));
	}
	else if (a->getCollisionBitmask() == 12 && b->getCollisionBitmask() == 15
		|| a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 12)
	{
		if (Trainer::m_Pokemons.size() == 0) {
			CCLOG("No Pokemon in the bag");
		}
		int idPokemon = random()%3;	
		
		//chuyen scene chien dau
		CCLOG("Has Pokemon");

	}

	return true;

}

void Town::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/Townmap1.tmx");
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
				mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
				Townbody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				Townbody->setCollisionBitmask(15);
				Townbody->setMass(14);
				Townbody->setContactTestBitmask(true);
				Townbody->setDynamic(true);
				Townbody->setRotationEnable(false);
				Townbody->setGravityEnable(false);
				mPlayer->GetSpriteFront()->setPhysicsBody(Townbody);
			}
			else continue;
		}
		else if (type == 2)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			TowngateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			TowngateWay->setCollisionBitmask(17);
			TowngateWay->setMass(16);
			TowngateWay->setContactTestBitmask(true);
			TowngateWay->setDynamic(false);
			TowngateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(TowngateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == 3)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			TowngateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			TowngateWay->setCollisionBitmask(19);
			TowngateWay->setMass(18);
			TowngateWay->setContactTestBitmask(true);
			TowngateWay->setDynamic(false);
			TowngateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(TowngateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == 4)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			TowngateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			TowngateWay->setCollisionBitmask(21);
			TowngateWay->setMass(20);
			TowngateWay->setContactTestBitmask(true);
			TowngateWay->setDynamic(false);
			TowngateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(TowngateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Town::updateCamera() {
	if (TownvisibleSize.width >= TowntileMapSize.width) {
		if (TownvisibleSize.height >= TowntileMapSize.height) {
			Towncamera->setPosition(TowntileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - TowntileMapSize.height / 2)>abs(TowntileMapSize.height / 2 - TownvisibleSize.height / 2)) {
				Towncamera->setPosition(TowntileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Towncamera->getPosition().y) ? (TowntileMapSize.height - TownvisibleSize.height / 2) : TownvisibleSize.height / 2);
			}
			else {
				Towncamera->setPosition(TowntileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (TownvisibleSize.height >= TowntileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - TowntileMapSize.width / 2)>abs(TowntileMapSize.width / 2 - TownvisibleSize.width / 2)) {
				Towncamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Towncamera->getPosition().y) ? (TowntileMapSize.width - TownvisibleSize.width / 2) : TownvisibleSize.width / 2, TowntileMapSize.height / 2);
			}
			else {
				Towncamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, TowntileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - TowntileMapSize.width / 2)>abs(TowntileMapSize.width / 2 - TownvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - TowntileMapSize.height / 2)>abs(TowntileMapSize.height / 2 - TownvisibleSize.height / 2)) {
				Towncamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Towncamera->getPosition().x) ? (TowntileMapSize.width - TownvisibleSize.width / 2) : TownvisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Towncamera->getPosition().y) ? (TowntileMapSize.height - TownvisibleSize.height / 2) : TownvisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - TowntileMapSize.width / 2)>abs(TowntileMapSize.width / 2 - TownvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - TowntileMapSize.height / 2)<abs(TowntileMapSize.height / 2 - TownvisibleSize.height / 2)) {
				Towncamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Towncamera->getPosition().x) ? (TowntileMapSize.width - TownvisibleSize.width / 2) : TownvisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - TowntileMapSize.width / 2)<abs(TowntileMapSize.width / 2 - TownvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - TowntileMapSize.height / 2)>abs(TowntileMapSize.height / 2 - TownvisibleSize.height / 2)) {
				Towncamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Towncamera->getPosition().y) ? (TowntileMapSize.height - TownvisibleSize.height / 2) : TownvisibleSize.height / 2);
			}
			else {
				Towncamera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}

}
void Town::update(float dt) {
	updateCamera();
	Buttons::getIntance()->UpdateButton(Towncamera->getPosition().x - 200, Towncamera->getPosition().y - 100);
}