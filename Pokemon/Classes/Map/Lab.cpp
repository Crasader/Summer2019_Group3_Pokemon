#include "Lab.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "Town.h"
#include "Model.h"
#include "Scene\BattleScene.h"

using namespace CocosDenshion;
Size labVisibleSize;
Size labTileMapSize;
int count = 0;
PhysicsBody* labBody, *labGateWay, *doctorBody;
Camera *labCamera;

Scene* Lab::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("LabScene.mp3", true);
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	labVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto map = ResourceManager::GetInstance()->GetTiledMapById(7);
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

	this->m_messageBox = ResourceManager::GetInstance()->GetSpriteById(130);
	auto scale_x = 0.7;
	auto scale_y = 0.7;
	this->m_messageBox->setScaleX(scale_x);
	this->m_messageBox->setScaleY(scale_y);
	this->m_messageBox->setVisible(false);
	this->m_messageBox->setPosition(Director::getInstance()->getVisibleSize().width / 1.88, Director::getInstance()->getVisibleSize().height / 4);
	this->addChild(this->m_messageBox, 0);
	this->m_labelLog = ResourceManager::GetInstance()->GetLabelById(0);
	this->m_labelLog->setAnchorPoint(Vec2::ZERO);
	this->m_labelLog->setScale(1.5);
	this->m_labelLog->setTextColor(Color4B::BLACK);
	this->m_labelLog->setPosition(this->m_messageBox->getContentSize().width * scale_x / 10, this->m_messageBox->getContentSize().height * scale_y / 1.2);
	this->m_messageBox->addChild(this->m_labelLog);
	return true;
}

void Lab::TypeWriter(float deltaTime)
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
		this->unschedule(schedule_selector(Lab::TypeWriter));
	}
}

void Lab::LogSetOpacity(GLubyte opacity)
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
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_DOCTOR)
		|| a->getCollisionBitmask() == Model::BITMASK_DOCTOR && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
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
		this->Log("fix ho bo may cai");
		this->m_stateLog = true;
		this->m_messageBox->setVisible(true);
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Lab::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	}
	return true;

}

void Lab::InitObject()
{
	auto map = ResourceManager::GetInstance()->GetTiledMapById(7);
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
			labBody->setCollisionBitmask(Model::BITMASK_PLAYER);
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
			m_doctor = ResourceManager::GetInstance()->GetSpriteById(122);
			m_doctor->setPosition(Vec2(posX, posY));
			doctorBody = PhysicsBody::createBox(m_doctor->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			doctorBody->setCollisionBitmask(Model::BITMASK_DOCTOR);
			doctorBody->setContactTestBitmask(true);
			doctorBody->setDynamic(false);
			doctorBody->setGravityEnable(false);
			m_doctor->setPhysicsBody(doctorBody);
			this->addChild(m_doctor, 10);
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
				labCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >labCamera->getPosition().x) ? (labTileMapSize.width - labVisibleSize.width / 2) : labVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >labCamera->getPosition().y) ? (labTileMapSize.height - labVisibleSize.height / 2) : labVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - labTileMapSize.width / 2)>abs(labTileMapSize.width / 2 - labVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - labTileMapSize.height / 2)<abs(labTileMapSize.height / 2 - labVisibleSize.height / 2)) {
				labCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >labCamera->getPosition().x) ? (labTileMapSize.width - labVisibleSize.width / 2) : labVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - labTileMapSize.width / 2)<abs(labTileMapSize.width / 2 - labVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - labTileMapSize.height / 2)>abs(labTileMapSize.height / 2 - labVisibleSize.height / 2)) {
				labCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >labCamera->getPosition().y) ? (labTileMapSize.height - labVisibleSize.height / 2) : labVisibleSize.height / 2);
			}
			else {
				labCamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}
void Lab::Log(string logg)
{
	this->m_labelLog->setString(logg);
	this->LogSetOpacity(0);
	this->m_labelLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(Lab::TypeWriter), 0.05);
}
bool Lab::onTouchBegan(Touch * touch, Event * e)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Beep.mp3", false);
	if(!m_stateLog){
		if (this->m_labelLog->getOpacity() == 0)
		{
			this->unschedule(schedule_selector(Lab::TypeWriter));
			this->LogSetOpacity(255);
			this->m_labelLog->setOpacity(255);
		}
	}
	else
	{
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
		contactListener->onContactBegin = CC_CALLBACK_1(Lab::onContactBegin, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
		
		scheduleUpdate();
	}
	return true;
}
void Lab::update(float dt) {
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(labCamera->getPosition().x - 200, labCamera->getPosition().y - 100);
}