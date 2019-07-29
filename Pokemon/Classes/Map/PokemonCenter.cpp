
#include "PokemonCenter.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "City.h"
#include "Model.h"

using namespace CocosDenshion;
USING_NS_CC;
Size pcvisibleSize;
Size pctileMapSize;

PhysicsBody* pcbody, *pcgateWay, *nursebody, *shopbody;
Camera *pccamera;

Scene* PokemonCenter::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = PokemonCenter::create();
	scene->addChild(layer);
	pccamera = scene->getDefaultCamera();
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PokemonCenter::init()
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("PokemonCenter.mp3", true);
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	pcvisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/PokemonCenter.tmx");
	pctileMapSize = map->getContentSize();
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
	up->removeFromParent();
	right->removeFromParent();
	left->removeFromParent();
	down->removeFromParent();
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);

	Buttons::GetIntance()->ButtonListener(this->mPlayer);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PokemonCenter::onContactBegin, this);
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

void PokemonCenter::TypeWriter(float deltaTime)
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
		this->unschedule(schedule_selector(PokemonCenter::TypeWriter));
	}
}

void PokemonCenter::LogSetOpacity(GLubyte opacity)
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

bool PokemonCenter::onContactBegin(PhysicsContact & contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_GATEWAY_TO_CITY)
		|| (a->getCollisionBitmask() == Model::BITMASK_GATEWAY_TO_CITY && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
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
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_NURSENPC)
		|| a->getCollisionBitmask() == Model::BITMASK_NURSENPC && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
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
		audio->playEffect("recovery.wav", false);
		Buttons::GetIntance()->Remove();
		this->Log("pokemon cua ban da duoc phuc hoi");
		this->m_stateLog = true;
		this->m_messageBox->setVisible(true);
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(PokemonCenter::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_SHOPNPC)
		|| a->getCollisionBitmask() == Model::BITMASK_SHOPNPC && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
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
		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(PokemonCenter::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	}
	return true;

}

void PokemonCenter::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/PokemonCenter.tmx");
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
			pcbody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			pcbody->setCollisionBitmask(Model::BITMASK_PLAYER);
			pcbody->setContactTestBitmask(true);
			pcbody->setDynamic(true);
			pcbody->setRotationEnable(false);
			pcbody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(pcbody);
		}
		else if (type== Model::MODLE_TYPE_NURSENPC)
		{
			m_nurse = ResourceManager::GetInstance()->GetSpriteById(126);
			m_nurse->setPosition(Vec2(posX, posY));
			m_nurse->setScale(0.8);
			nursebody = PhysicsBody::createBox(m_nurse->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			nursebody->setCollisionBitmask(Model::BITMASK_NURSENPC);
			nursebody->setContactTestBitmask(true);
			nursebody->setDynamic(false);
			nursebody->setGravityEnable(false);
			m_nurse->setPhysicsBody(nursebody);
			this->addChild(m_nurse, 10);
		}
		else if (type == Model::MODLE_TYPE_SHOPNPC)
		{
			m_shop = ResourceManager::GetInstance()->GetSpriteById(127);
			m_shop->setPosition(Vec2(posX, posY));
			m_shop->setScale(0.8);
			shopbody = PhysicsBody::createBox(m_shop->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			shopbody->setCollisionBitmask(Model::BITMASK_SHOPNPC);
			shopbody->setContactTestBitmask(true);
			shopbody->setDynamic(false);
			shopbody->setGravityEnable(false);
			m_shop->setPhysicsBody(shopbody);
			this->addChild(m_shop, 10);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			pcgateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			pcgateWay->setCollisionBitmask(Model::BITMASK_GATEWAY_TO_CITY);
			pcgateWay->setContactTestBitmask(true);
			pcgateWay->setDynamic(false);
			pcgateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(pcgateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void PokemonCenter::UpdateCamera() {
	if (pcvisibleSize.width >= pctileMapSize.width) {
		if (pcvisibleSize.height >= pctileMapSize.height) {
			pccamera->setPosition(pctileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - pctileMapSize.height / 2)>abs(pctileMapSize.height / 2 - pcvisibleSize.height / 2)) {
				pccamera->setPosition(pctileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >pccamera->getPosition().y) ? (pctileMapSize.height - pcvisibleSize.height / 2) : pcvisibleSize.height / 2);
			}
			else {
				pccamera->setPosition(pctileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (pcvisibleSize.height >= pctileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - pctileMapSize.width / 2)>abs(pctileMapSize.width / 2 - pcvisibleSize.width / 2)) {
				pccamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >pccamera->getPosition().y) ? (pctileMapSize.width - pcvisibleSize.width / 2) : pcvisibleSize.width / 2, pctileMapSize.height / 2);
			}
			else {
				pccamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, pctileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - pctileMapSize.width / 2)>abs(pctileMapSize.width / 2 - pcvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - pctileMapSize.height / 2)>abs(pctileMapSize.height / 2 - pcvisibleSize.height / 2)) {
				pccamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >pccamera->getPosition().x) ? (pctileMapSize.width - pcvisibleSize.width / 2) : pcvisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >pccamera->getPosition().y) ? (pctileMapSize.height - pcvisibleSize.height / 2) : pcvisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - pctileMapSize.width / 2)>abs(pctileMapSize.width / 2 - pcvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - pctileMapSize.height / 2)<abs(pctileMapSize.height / 2 - pcvisibleSize.height / 2)) {
				pccamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >pccamera->getPosition().x) ? (pctileMapSize.width - pcvisibleSize.width / 2) : pcvisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - pctileMapSize.width / 2)<abs(pctileMapSize.width / 2 - pcvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - pctileMapSize.height / 2)>abs(pctileMapSize.height / 2 - pcvisibleSize.height / 2)) {
				pccamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >pccamera->getPosition().y) ? (pctileMapSize.height - pcvisibleSize.height / 2) : pcvisibleSize.height / 2);
			}
			else {
				pccamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}
void PokemonCenter::Log(string logg)
{
	this->m_labelLog->setString(logg);
	this->LogSetOpacity(0);
	this->m_labelLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(PokemonCenter::TypeWriter), 0.05);
}
bool PokemonCenter::onTouchBegan(Touch * touch, Event * e)
{
	auto audio = SimpleAudioEngine::getInstance();
	audio->playEffect("Beep.mp3", false);
	if (!m_stateLog) {
		if (this->m_labelLog->getOpacity() == 0)
		{
			this->unschedule(schedule_selector(PokemonCenter::TypeWriter));
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
		contactListener->onContactBegin = CC_CALLBACK_1(PokemonCenter::onContactBegin, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

		scheduleUpdate();
	}
	return true;
}
void PokemonCenter::update(float dt)
{
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(pccamera->getPosition().x - 200, pccamera->getPosition().y - 100);
}

