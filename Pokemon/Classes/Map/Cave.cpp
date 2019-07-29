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

PhysicsBody* caveBody, *caveGateWay, *enteiBody;
Camera *caveCamera;

Scene * Cave::createScene()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Sound/CaveScene.mp3", true);
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Cave::create();
	scene->addChild(layer);
	caveCamera = scene->getDefaultCamera();
	return scene;
}

void Cave::TypeWriter(float deltaTime)
{
	if (writing < this->m_labelLog->getStringLength())
	{
		auto letter = this->m_labelLog->getLetter(writing);
		if (letter != nullptr)
		{
			letter->setOpacity(255);
		}
		writing++;
	}
	else
	{
		writing = 0;
		this->m_labelLog->setOpacity(255);
		this->unschedule(schedule_selector(Cave::TypeWriter));
	}
}

void Cave::LogSetOpacity(GLubyte opacity)
{
	for (int i = 0; i < this->m_labelLog->getStringLength(); i++)
	{
		auto letter = this->m_labelLog->getLetter(i);
		if (letter != nullptr)
		{
			letter->setOpacity(opacity);
		}
	}
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
	this->m_messageBox = ResourceManager::GetInstance()->GetSpriteById(130);
	auto scale_x = 0.7;
	auto scale_y = 0.7;
	this->m_messageBox->setScaleX(scale_x);
	this->m_messageBox->setScaleY(scale_y);
	this->m_messageBox->setVisible(false);
	this->m_messageBox->setPosition(Director::getInstance()->getVisibleSize().width / 1.76, Director::getInstance()->getVisibleSize().height / 1.5);
	this->addChild(this->m_messageBox, 0);
	this->m_labelLog = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelLog->setAnchorPoint(Vec2::ZERO);
	this->m_labelLog->setScale(1.5);
	this->m_labelLog->setTextColor(Color4B::BLACK);
	this->m_labelLog->setPosition(this->m_messageBox->getContentSize().width * scale_x / 10, this->m_messageBox->getContentSize().height * scale_y / 1.2);
	this->m_messageBox->addChild(this->m_labelLog);
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
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_WORLD && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
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
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ENTEI)
		|| a->getCollisionBitmask() == Model::BITMASK_ENTEI && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
	{
		switch (Buttons::state)
		{
		case 1:
			mPlayer->StopWalkUp();
			break;
		case 2:
			mPlayer->StopWalkRight();
			break;
		case 3:
			mPlayer->StopWalkLeft();
			break;
		case 4:
			mPlayer->StopWalkDown();
			break;
		default:
			break;
		}
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("Beep.mp3", false);
		Buttons::GetIntance()->Remove();
		this->Log("Roar !");
		this->m_stateLog = true;
		this->m_messageBox->setVisible(true);
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Cave::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		Model::ENTEI = false;
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
		else if (type==Model::MODLE_TYPE_CAVE_GATE) {
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
		else
		{
			if (Model::ENTEI==true)
			{
				entei = Sprite::create("res/0.png");
				entei->setPosition(Vec2(posX, posY));
				entei->setScale(2);
				enteiBody = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				enteiBody->setCollisionBitmask(Model::BITMASK_ENTEI);
				enteiBody->setContactTestBitmask(true);
				enteiBody->setDynamic(false);
				enteiBody->setGravityEnable(false);
				entei->setPhysicsBody(enteiBody);
				this->addChild(entei, 10);
			}
			else
			{
			}
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

void Cave::Log(string logg)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Beep.mp3", false);
	this->m_labelLog->setString(logg);
	this->LogSetOpacity(0);
	this->m_labelLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(Cave::TypeWriter), 0.05);
}

bool Cave::onTouchBegan(Touch * touch, Event * e)
{
	if (m_stateLog == false) {
		if (this->m_labelLog->getOpacity() == 0)
		{
			this->unschedule(schedule_selector(Cave::TypeWriter));
			this->LogSetOpacity(255);
			this->m_labelLog->setOpacity(255);
		}
	}
	else
	{
		removeChild(entei, true);
		m_stateLog = false;
		this->m_messageBox->setVisible(false);
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
	}
	return true;
}

void Cave::update(float dt)
{
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(caveCamera->getPosition().x - 200, caveCamera->getPosition().y - 100);
}
