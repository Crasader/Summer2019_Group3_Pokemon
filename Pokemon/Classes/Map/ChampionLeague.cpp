#include "ChampionLeague.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "Model.h"

using namespace CocosDenshion;
USING_NS_CC;

Size leagueVisibleSize;
Size leagueTileMapSize;

Layer *layer_UI_League;
PhysicsBody* leagueBody;
Camera *leagueCamera, *cameraUILeague;

Scene * League::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = League::create();
	scene->addChild(layer);
	leagueCamera = scene->getDefaultCamera();
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool League::init()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Sound/ChampionLeague.mp3", true);
	if (!Layer::init())
	{
		return false;
	}

	leagueVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/League.tmx");
	leagueTileMapSize = map->getContentSize();
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
	Button *bag = Buttons::GetIntance()->GetButtonBag();
	Button *tips = Buttons::GetIntance()->GetButtonTips();

	layer_UI_League = Layer::create();
	cameraUILeague = Camera::create();
	cameraUILeague->setCameraMask(2);
	cameraUILeague->setCameraFlag(CameraFlag::USER1);
	up->setCameraMask(2);
	bag->setCameraMask(2);
	tips->setCameraMask(2);
	layer_UI_League->addChild(cameraUILeague, 2);
	layer_UI_League->addChild(up);
	layer_UI_League->addChild(bag);
	layer_UI_League->addChild(tips);
	this->addChild(layer_UI_League, 100);


	Buttons::GetIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(League::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool League::onContactBegin(PhysicsContact & contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_WORLD && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WORLD))
	{
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("WallBump.mp3", false);
		switch (Buttons::state)
		{
		case 1:
			mPlayer->GetSpriteFront()->stopActionByTag(0);
			mPlayer->GetSpriteFront()->setPositionY(mPlayer->GetSpriteFront()->getPositionY() - 1);
			break;
		case 2:
			mPlayer->GetSpriteFront()->stopActionByTag(6);
			mPlayer->GetSpriteFront()->setPositionX(mPlayer->GetSpriteFront()->getPositionX() - 1);
			break;
		case 3:
			mPlayer->GetSpriteFront()->stopActionByTag(4);
			mPlayer->GetSpriteFront()->setPositionX(mPlayer->GetSpriteFront()->getPositionX() + 1);
			break;
		case 4:
			mPlayer->GetSpriteFront()->stopActionByTag(2);
			mPlayer->GetSpriteFront()->setPositionY(mPlayer->GetSpriteFront()->getPositionY() + 1);
			break;
		default:
			break;
		}
	}
	return true;
}

void League::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/League.tmx");
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
			mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkleft/1.png");
			mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
			leagueBody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			leagueBody->setCollisionBitmask(Model::BITMASK_PLAYER);
			leagueBody->setContactTestBitmask(true);
			leagueBody->setDynamic(true);
			leagueBody->setRotationEnable(false);
			leagueBody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(leagueBody);
		}
	}
}

void League::UpdateCamera() {
	if (leagueVisibleSize.width >= leagueTileMapSize.width) {
		if (leagueVisibleSize.height >= leagueTileMapSize.height) {
			leagueCamera->setPosition(leagueTileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - leagueTileMapSize.height / 2)>abs(leagueTileMapSize.height / 2 - leagueVisibleSize.height / 2)) {
				leagueCamera->setPosition(leagueTileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >leagueCamera->getPosition().y) ? (leagueTileMapSize.height - leagueVisibleSize.height / 2) : leagueVisibleSize.height / 2);
			}
			else {
				leagueCamera->setPosition(leagueTileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (leagueVisibleSize.height >= leagueTileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - leagueTileMapSize.width / 2)>abs(leagueTileMapSize.width / 2 - leagueVisibleSize.width / 2)) {
				leagueCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >leagueCamera->getPosition().y) ? (leagueTileMapSize.width - leagueVisibleSize.width / 2) : leagueVisibleSize.width / 2, leagueTileMapSize.height / 2);
			}
			else {
				leagueCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, leagueTileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - leagueTileMapSize.width / 2)>abs(leagueTileMapSize.width / 2 - leagueVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - leagueTileMapSize.height / 2)>abs(leagueTileMapSize.height / 2 - leagueVisibleSize.height / 2)) {
				leagueCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >leagueCamera->getPosition().x) ? (leagueTileMapSize.width - leagueVisibleSize.width / 2) : leagueVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >leagueCamera->getPosition().y) ? (leagueTileMapSize.height - leagueVisibleSize.height / 2) : leagueVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - leagueTileMapSize.width / 2)>abs(leagueTileMapSize.width / 2 - leagueVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - leagueTileMapSize.height / 2)<abs(leagueTileMapSize.height / 2 - leagueVisibleSize.height / 2)) {
				leagueCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >leagueCamera->getPosition().x) ? (leagueTileMapSize.width - leagueVisibleSize.width / 2) : leagueVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - leagueTileMapSize.width / 2)<abs(leagueTileMapSize.width / 2 - leagueVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - leagueTileMapSize.height / 2)>abs(leagueTileMapSize.height / 2 - leagueVisibleSize.height / 2)) {
				leagueCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >leagueCamera->getPosition().y) ? (leagueTileMapSize.height - leagueVisibleSize.height / 2) : leagueVisibleSize.height / 2);
			}
			else {
				leagueCamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}

int leagueSum = 0;

void League::UpdatePlayer(float dt) {
	leagueSum++;
	if (leagueSum >30) {
		if (mPlayer->isMoveDown) {
			mPlayer->StopWalkDown();
			mPlayer->WalkDown();
		}
		else if (mPlayer->isMoveLeft) {
			mPlayer->StopWalkLeft();
			mPlayer->WalkLeft();
		}
		else if (mPlayer->isMoveUp) {
			mPlayer->StopWalkUp();
			mPlayer->WalkUp();
		}
		else if (mPlayer->isMoveRight) {
			mPlayer->StopWalkRight();
			mPlayer->WalkRight();
		}
		else
		{
		}
		leagueSum = 0;
	}
}


void League::update(float dt)
{
	UpdatePlayer(dt);
	UpdateCamera();
}
