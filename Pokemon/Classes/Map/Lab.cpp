#include "Lab.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "Town.h"
#include "Model.h"

Size labVisibleSize;
Size labTileMapSize;
PhysicsBody* labBody, *labGateWay, *doctorBody;
Camera *labCamera;



Scene* Lab::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Lab::create();
	scene->addChild(layer);
	labCamera = scene->getDefaultCamera();
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

	labVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/Lab.tmx");
	labTileMapSize = map->getContentSize();
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
	contactListener->onContactBegin = CC_CALLBACK_1(Lab::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool Lab::onContactBegin(PhysicsContact& contact)

{

	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_GATEWAY_TO_TOWN)
		|| a->getCollisionBitmask() == Model::BITMASK_GATEWAY_TO_TOWN && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Town::previousScene = Model::PRESCENE_LAB_TO_TOWN;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Town::createScene()));
	}

	return true;

}

void Lab::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/Lab.tmx");
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
			labBody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			labBody->setCollisionBitmask(17);
			labBody->setMass(16);
			labBody->setContactTestBitmask(true);
			labBody->setDynamic(true);
			labBody->setRotationEnable(false);
			labBody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(labBody);
		}
		else if(type == Model::MODLE_TYPE_GATEWAY_LAB) {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			labGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			labGateWay->setCollisionBitmask(Model::BITMASK_GATEWAY_TO_TOWN);
			labGateWay->setContactTestBitmask(true);
			labGateWay->setDynamic(false);
			labGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(labGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else {
			doctor = Sprite::create("res/oak_down.png");
			doctor->setPosition(Vec2(posX, posY));
			doctorBody = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			doctorBody->setCollisionBitmask(Model::BITMASK_DOCTOR);
			doctorBody->setContactTestBitmask(true);
			doctorBody->setDynamic(false);
			doctorBody->setGravityEnable(false);
			doctor->setPhysicsBody(doctorBody);
			this->addChild(doctor, 10);
		}
	}

}

void Lab::UpdateCamera() {
	if (labVisibleSize.width >= labTileMapSize.width) {
		if (labVisibleSize.height >= labTileMapSize.height) {
			labCamera->setPosition(labTileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - labTileMapSize.height / 2)>abs(labTileMapSize.height / 2 - labVisibleSize.height / 2)) {
				labCamera->setPosition(labTileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >labCamera->getPosition().y) ? (labTileMapSize.height - labVisibleSize.height / 2) : labVisibleSize.height / 2);
			}
			else {
				labCamera->setPosition(labTileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (labVisibleSize.height >= labTileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - labTileMapSize.width / 2)>abs(labTileMapSize.width / 2 - labVisibleSize.width / 2)) {
				labCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >labCamera->getPosition().y) ? (labTileMapSize.width - labVisibleSize.width / 2) : labVisibleSize.width / 2, labTileMapSize.height / 2);
			}
			else {
				labCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, labTileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - labTileMapSize.width / 2)>abs(labTileMapSize.width / 2 - labVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - labTileMapSize.height / 2)>abs(labTileMapSize.height / 2 - labVisibleSize.height / 2)) {
				labCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >labCamera->getPosition().x) ? (labTileMapSize.width - labVisibleSize.width / 2) : labVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >labCamera->getPosition().y) ? (labTileMapSize.height - labVisibleSize.height / 2) : labVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - labTileMapSize.width / 2)>abs(labTileMapSize.width / 2 - labVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - labTileMapSize.height / 2)<abs(labTileMapSize.height / 2 - labVisibleSize.height / 2)) {
				labCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >labCamera->getPosition().x) ? (labTileMapSize.width - labVisibleSize.width / 2) : labVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - labTileMapSize.width / 2)<abs(labTileMapSize.width / 2 - labVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - labTileMapSize.height / 2)>abs(labTileMapSize.height / 2 - labVisibleSize.height / 2)) {
				labCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >labCamera->getPosition().y) ? (labTileMapSize.height - labVisibleSize.height / 2) : labVisibleSize.height / 2);
			}
			else {
				labCamera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}

}
void Lab::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(labCamera->getPosition().x - 200, labCamera->getPosition().y - 100);
}