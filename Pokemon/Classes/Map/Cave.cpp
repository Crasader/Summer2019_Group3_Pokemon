#include "Cave.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "City.h"
#include "Model.h"

using namespace CocosDenshion;
USING_NS_CC;

Size caveVisibleSize;
Size caveTileMapSize;

PhysicsBody* caveBody, *caveGateWay;
Camera *caveCamera;

Scene * Cave::createScene()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("CaveScene.mp3", true);
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Cave::create();
	scene->addChild(layer);
	caveCamera = scene->getDefaultCamera();
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

	caveVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/Cave.tmx");
	caveTileMapSize = map->getContentSize();
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
				physics->setCollisionBitmask(Model::BITMASK_WORLD);
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				physics->setGravityEnable(false);
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
	contactListener->onContactBegin = CC_CALLBACK_1(Cave::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Cave::onContactBegin(PhysicsContact & contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_CAVE_GATE && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_CAVE_GATE))
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, City::createScene()));
	}

	return true;

}

void Cave::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/Cave.tmx");
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
			caveBody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			caveBody->setCollisionBitmask(Model::BITMASK_PLAYER);
			caveBody->setContactTestBitmask(true);
			caveBody->setDynamic(true);
			caveBody->setRotationEnable(false);
			caveBody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(caveBody);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			caveGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			caveGateWay->setCollisionBitmask(Model::BITMASK_CAVE_GATE);
			caveGateWay->setContactTestBitmask(true);
			caveGateWay->setDynamic(false);
			caveGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(caveGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Cave::UpdateCamera() {
	if (caveVisibleSize.width >= caveTileMapSize.width) {
		if (caveVisibleSize.height >= caveTileMapSize.height) {
			caveCamera->setPosition(caveTileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - caveTileMapSize.height / 2)>abs(caveTileMapSize.height / 2 - caveVisibleSize.height / 2)) {
				caveCamera->setPosition(caveTileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >caveCamera->getPosition().y) ? (caveTileMapSize.height - caveVisibleSize.height / 2) : caveVisibleSize.height / 2);
			}
			else {
				caveCamera->setPosition(caveTileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (caveVisibleSize.height >= caveTileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - caveTileMapSize.width / 2)>abs(caveTileMapSize.width / 2 - caveVisibleSize.width / 2)) {
				caveCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >caveCamera->getPosition().y) ? (caveTileMapSize.width - caveVisibleSize.width / 2) : caveVisibleSize.width / 2, caveTileMapSize.height / 2);
			}
			else {
				caveCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, caveTileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - caveTileMapSize.width / 2)>abs(caveTileMapSize.width / 2 - caveVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - caveTileMapSize.height / 2)>abs(caveTileMapSize.height / 2 - caveVisibleSize.height / 2)) {
				caveCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >caveCamera->getPosition().x) ? (caveTileMapSize.width - caveVisibleSize.width / 2) : caveVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >caveCamera->getPosition().y) ? (caveTileMapSize.height - caveVisibleSize.height / 2) : caveVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - caveTileMapSize.width / 2)>abs(caveTileMapSize.width / 2 - caveVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - caveTileMapSize.height / 2)<abs(caveTileMapSize.height / 2 - caveVisibleSize.height / 2)) {
				caveCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >caveCamera->getPosition().x) ? (caveTileMapSize.width - caveVisibleSize.width / 2) : caveVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - caveTileMapSize.width / 2)<abs(caveTileMapSize.width / 2 - caveVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - caveTileMapSize.height / 2)>abs(caveTileMapSize.height / 2 - caveVisibleSize.height / 2)) {
				caveCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >caveCamera->getPosition().y) ? (caveTileMapSize.height - caveVisibleSize.height / 2) : caveVisibleSize.height / 2);
			}
			else {
				caveCamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}

void Cave::update(float dt)
{
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(caveCamera->getPosition().x - 200, caveCamera->getPosition().y - 100);
}
