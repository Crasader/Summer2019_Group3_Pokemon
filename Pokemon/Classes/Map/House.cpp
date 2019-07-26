#include "House.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "Town.h"
#include "Popup.h"
#include "Model.h"

using namespace CocosDenshion;
USING_NS_CC;

Size houseVisibleSize;
Size houseTileMapSize;

PhysicsBody* houseBody, *houseGateWay;
Camera *houseCamera;

Scene * House::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = House::create();
	scene->addChild(layer);
	houseCamera = scene->getDefaultCamera();
	return scene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool House::init()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("HouseScene.mp3", true);
	if (!Layer::init())
	{
		return false;
	}
	houseVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto map = ResourceManager::GetInstance()->GetTiledMapById(1);
	houseTileMapSize = map->getContentSize();
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
	Button *bag = Buttons::GetIntance()->GetButtonBag();
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);
	addChild(bag, 100);

	Buttons::GetIntance()->ButtonListener(this->mPlayer);
	//Buttons::GetIntance()->ButtonBagListener(this, Housecamera);
	Buttons::GetIntance()->GetButtonBag()->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(false);
			string str = "My bag - Gold: " + to_string(Bag::GetInstance()->GetGold()) + " $";
			UICustom::Popup *popup = UICustom::Popup::createBag(str);
			popup->removeFromParent();
			popup->setAnchorPoint(Vec2(0.5, 0.5));
			popup->setPosition(houseCamera->getPosition().x - popup->getContentSize().width/2,
				houseCamera->getPosition().y - popup->getContentSize().height / 2);
			this->addChild(popup,101);
		}
	});
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(House::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();
	return true;
}

bool House::onContactBegin(PhysicsContact & contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_HOUSE_GATE && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_HOUSE_GATE))
	{
		Buttons::GetIntance()->Remove();
		Director::getInstance()->getRunningScene()->pause();
		Town::previousScene = Model::PRESCENE_HOUSE_TO_TOWN;
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Town::createScene()));
	}
	if ((a->getCollisionBitmask() == Model::BITMASK_WORLD && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WORLD))
	{
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

void House::InitObject()
{
	auto map = ResourceManager::GetInstance()->GetTiledMapById(1);
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
			houseBody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			houseBody->setCollisionBitmask(Model::BITMASK_PLAYER);
			houseBody->setContactTestBitmask(true);
			houseBody->setDynamic(true);
			houseBody->setRotationEnable(false);
			houseBody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(houseBody);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			houseGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			houseGateWay->setCollisionBitmask(Model::BITMASK_HOUSE_GATE);
			houseGateWay->setContactTestBitmask(true);
			houseGateWay->setDynamic(false);
			houseGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(houseGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}
}

void House::UpdateCamera() {
	if (houseVisibleSize.width >= houseTileMapSize.width) {
		if (houseVisibleSize.height >= houseTileMapSize.height) {
			houseCamera->setPosition(houseTileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - houseTileMapSize.height / 2)>abs(houseTileMapSize.height / 2 - houseVisibleSize.height / 2)) {
				houseCamera->setPosition(houseTileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >houseCamera->getPosition().y) ? (houseTileMapSize.height - houseVisibleSize.height / 2) : houseVisibleSize.height / 2);
			}
			else {
				houseCamera->setPosition(houseTileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (houseVisibleSize.height >= houseTileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - houseTileMapSize.width / 2)>abs(houseTileMapSize.width / 2 - houseVisibleSize.width / 2)) {
				houseCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >houseCamera->getPosition().y) ? (houseTileMapSize.width - houseVisibleSize.width / 2) : houseVisibleSize.width / 2, houseTileMapSize.height / 2);
			}
			else {
				houseCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, houseTileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - houseTileMapSize.width / 2)>abs(houseTileMapSize.width / 2 - houseVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - houseTileMapSize.height / 2)>abs(houseTileMapSize.height / 2 - houseVisibleSize.height / 2)) {
				houseCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >houseCamera->getPosition().x) ? (houseTileMapSize.width - houseVisibleSize.width / 2) : houseVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >houseCamera->getPosition().y) ? (houseTileMapSize.height - houseVisibleSize.height / 2) : houseVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - houseTileMapSize.width / 2)>abs(houseTileMapSize.width / 2 - houseVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - houseTileMapSize.height / 2)<abs(houseTileMapSize.height / 2 - houseVisibleSize.height / 2)) {
				houseCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >houseCamera->getPosition().x) ? (houseTileMapSize.width - houseVisibleSize.width / 2) : houseVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - houseTileMapSize.width / 2)<abs(houseTileMapSize.width / 2 - houseVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - houseTileMapSize.height / 2)>abs(houseTileMapSize.height / 2 - houseVisibleSize.height / 2)) {
				houseCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >houseCamera->getPosition().y) ? (houseTileMapSize.height - houseVisibleSize.height / 2) : houseVisibleSize.height / 2);
			}
			else {
				houseCamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}

void House::update(float dt)
{
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(houseCamera->getPosition().x - 200, houseCamera->getPosition().y - 100);
}