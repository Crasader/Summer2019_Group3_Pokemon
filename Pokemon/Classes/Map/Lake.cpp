#include "Lake.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "City.h"
#include "Model.h"

using namespace CocosDenshion;
USING_NS_CC;
Size lakevisibleSize;
Size laketileMapSize;

PhysicsBody* lakebody, *lakegateWay, *suicuneBody;
Camera *lakecamera;



Scene* Lake::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Lake::create();
	scene->addChild(layer);
	lakecamera = scene->getDefaultCamera();
	return scene;
}

void Lake::TypeWriter(float deltaTime)
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
		this->unschedule(schedule_selector(Lake::TypeWriter));
	}
}

void Lake::LogSetOpacity(GLubyte opacity)
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

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Lake::init()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("LakeScene.mp3", true);
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
	contactListener->onContactBegin = CC_CALLBACK_1(Lake::onContactBegin, this);
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
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_SUICUNE)
		|| a->getCollisionBitmask() == Model::BITMASK_SUICUNE && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
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
		this->Log("Meow ?");
		this->m_stateLog = true;
		this->m_messageBox->setVisible(true);
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Lake::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		
		if (Model::SUICUNE == false)
		{
			this->Log("really nigga");
		}
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
		else if (type == Model::MODLE_TYPE_LAKE_GATE)
		{
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
		else
		{
			if (Model::SUICUNE==true)
			{
				suicune = Sprite::create("res/2.png");
				suicune->setPosition(Vec2(posX, posY));
				suicune->setScale(2);
				suicuneBody = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				suicuneBody->setCollisionBitmask(Model::BITMASK_SUICUNE);
				suicuneBody->setContactTestBitmask(true);
				suicuneBody->setDynamic(false);
				suicuneBody->setGravityEnable(false);
				suicune->setPhysicsBody(suicuneBody);
				this->addChild(suicune, 10);
			}
			else
			{
			}
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
void Lake::Log(string logg)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Beep.mp3", false);
	this->m_labelLog->setString(logg);
	this->LogSetOpacity(0);
	this->m_labelLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(Lake::TypeWriter), 0.05);
}
bool Lake::onTouchBegan(Touch * touch, Event * e)
{
	Model::SUICUNE = false;
	if (m_stateLog == false) {
		if (this->m_labelLog->getOpacity() == 0)
		{
			this->unschedule(schedule_selector(Lake::TypeWriter));
			this->LogSetOpacity(255);
			this->m_labelLog->setOpacity(255);
		}
	}
	else
	{
		m_stateLog = false;
		this->m_messageBox->setVisible(false);
		//removeChild(suicune, true);
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
	}
	return true;
}
void Lake::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(lakecamera->getPosition().x - 200, lakecamera->getPosition().y - 100);
}