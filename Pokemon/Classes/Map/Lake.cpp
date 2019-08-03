#include "Lake.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "City.h"
#include "Scene\BattleScene.h"
#include "Model.h"
#include "Popup.h"

using namespace CocosDenshion;
USING_NS_CC;
Size lakeVisibleSize;
Size laketileMapSize;
vector<Vec2> lake_point;
float lake_tick = 0;
PhysicsBody* lakebody, *lakegateWay, *suicuneBody;
Camera *lakecamera, *cameraUILake;
Layer *layer_UI_Lake;


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
	audio->playBackgroundMusic("res/Sound/LakeScene.mp3", true);
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	lakeVisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	map = ResourceManager::GetInstance()->GetTiledMapById(9);
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

	InitGrass();

	InitObject();
	
	Button *up = Buttons::GetIntance()->GetButtonUp();
	Button *bag = Buttons::GetIntance()->GetButtonBag();
	Button *tips = Buttons::GetIntance()->GetButtonTips();

	layer_UI_Lake = Layer::create();
	layer_UI_Lake->setScale(lakeVisibleSize.width / layer_UI_Lake->getContentSize().width, lakeVisibleSize.height / layer_UI_Lake->getContentSize().height);
	up->setPosition(Vec2(lakeVisibleSize.width / 7.2, lakeVisibleSize.height / 3.6));
	bag->setPosition(Vec2(lakeVisibleSize.width / 1.09, lakeVisibleSize.height / 1.09));
	tips->setPosition(Vec2(lakeVisibleSize.width / 20, lakeVisibleSize.height / 1.09));
	cameraUILake = Camera::create();
	cameraUILake->setCameraMask(2);
	cameraUILake->setCameraFlag(CameraFlag::USER1);
	up->setCameraMask(2);
	bag->setCameraMask(2);
	tips->setCameraMask(2);
	layer_UI_Lake->addChild(cameraUILake, 2);
	layer_UI_Lake->addChild(up);
	layer_UI_Lake->addChild(bag);
	layer_UI_Lake->addChild(tips);
	this->addChild(layer_UI_Lake, 100);

	Buttons::GetIntance()->ButtonListener(this->mPlayer);
	
	Buttons::GetIntance()->GetButtonBag()->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Buttons::GetIntance()->GetButtonBag()->setTouchEnabled(false);
			string str = "My bag - Gold: " + to_string(Bag::GetInstance()->GetGold()) + " $";
			UICustom::Popup *popup = UICustom::Popup::createBag(str);
			popup->removeFromParent();
			popup->setAnchorPoint(Vec2(0.5, 0.5));
			popup->setPosition(lakecamera->getPosition().x - popup->getContentSize().width / 2,
				lakecamera->getPosition().y - popup->getContentSize().height / 2);
			this->addChild(popup, 101);
		}
	});

	Buttons::GetIntance()->GetButtonTips()->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			Buttons::GetIntance()->GetButtonTips()->setTouchEnabled(false);
			UICustom::Popup *popup = UICustom::Popup::createAsMessage("Doctor", Model::GetTipsGame());
			popup->removeFromParent();
			popup->setAnchorPoint(Vec2(0.5, 0.5));
			popup->setPosition(lakecamera->getPosition().x - popup->getContentSize().width / 2,
				lakecamera->getPosition().y - popup->getContentSize().height / 2);
			this->addChild(popup, 101);
		}
	});
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
	this->addChild(this->m_messageBox, 10);
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
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_WORLD && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WORLD))
	{
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/WallBump.mp3", false);
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
		audio->playEffect("res/Sound/Beep.mp3", false);
		//Buttons::GetIntance()->SetTouchDisable();
		this->Log("Suisuiiiii!");
		this->m_messageBox->setVisible(true);
		touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Lake::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		auto listener = CallFunc::create([this]() {
			if (this->getTag() == 10)
			{
				Model::SUICUNE = false;
				this->stopActionByTag(100);
			}
		});
		auto rp = RepeatForever::create(Spawn::create(listener, nullptr));
		rp->setTag(100);
		this->runAction(rp);
	}
	return true;

}

void Lake::InitObject()
{
	auto map = ResourceManager::GetInstance()->GetTiledMapById(9);
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
			mPlayer->GetSpriteFront()->setScale(1.5);
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
			suicune = ResourceManager::GetInstance()->GetSpriteById(150);
			if (Model::SUICUNE==true)
			{
				suicune->setPosition(Vec2(posX, posY));
				suicune->setScale(2);
				suicuneBody = PhysicsBody::createBox(suicune->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
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

void Lake::InitGrass()
{
	auto grass = map->getLayer("grass");
	int width = grass->getLayerSize().width;
	int height = grass->getLayerSize().height;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			auto tilePokemon = grass->getTileAt(Vec2(i, j));
			if (tilePokemon != NULL)
			{
				lake_point.push_back(tilePokemon->getPosition());
			}
		}
	}
}

void Lake::UpdateCamera() {
	if (lakeVisibleSize.width >= laketileMapSize.width) {
		if (lakeVisibleSize.height >= laketileMapSize.height) {
			lakecamera->setPosition(laketileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - laketileMapSize.height / 2)>abs(laketileMapSize.height / 2 - lakeVisibleSize.height / 2)) {
				lakecamera->setPosition(laketileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >lakecamera->getPosition().y) ? (laketileMapSize.height - lakeVisibleSize.height / 2) : lakeVisibleSize.height / 2);
			}
			else {
				lakecamera->setPosition(laketileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (lakeVisibleSize.height >= laketileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - laketileMapSize.width / 2)>abs(laketileMapSize.width / 2 - lakeVisibleSize.width / 2)) {
				lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >lakecamera->getPosition().y) ? (laketileMapSize.width - lakeVisibleSize.width / 2) : lakeVisibleSize.width / 2, laketileMapSize.height / 2);
			}
			else {
				lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, laketileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - laketileMapSize.width / 2)>abs(laketileMapSize.width / 2 - lakeVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - laketileMapSize.height / 2)>abs(laketileMapSize.height / 2 - lakeVisibleSize.height / 2)) {
				lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >lakecamera->getPosition().x) ? (laketileMapSize.width - lakeVisibleSize.width / 2) : lakeVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >lakecamera->getPosition().y) ? (laketileMapSize.height - lakeVisibleSize.height / 2) : lakeVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - laketileMapSize.width / 2)>abs(laketileMapSize.width / 2 - lakeVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - laketileMapSize.height / 2)<abs(laketileMapSize.height / 2 - lakeVisibleSize.height / 2)) {
				lakecamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >lakecamera->getPosition().x) ? (laketileMapSize.width - lakeVisibleSize.width / 2) : lakeVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - laketileMapSize.width / 2)<abs(laketileMapSize.width / 2 - lakeVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - laketileMapSize.height / 2)>abs(laketileMapSize.height / 2 - lakeVisibleSize.height / 2)) {
				lakecamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >lakecamera->getPosition().y) ? (laketileMapSize.height - lakeVisibleSize.height / 2) : lakeVisibleSize.height / 2);
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
	audio->playEffect("res/Sound/Beep.mp3", false);
	this->m_labelLog->setString(logg);
	this->LogSetOpacity(0);
	this->m_labelLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(Lake::TypeWriter), 0.05);
}
bool Lake::onTouchBegan(Touch * touch, Event * e)
{
	if (this->m_labelLog->getOpacity() == 0)
	{
		this->unschedule(schedule_selector(Lake::TypeWriter));
		this->LogSetOpacity(255);
		this->m_labelLog->setOpacity(255);
		/*auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Lake::onTouchEnd, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);*/
	}
	else
	{
		this->m_messageBox->setVisible(false);
		vector<Pokemon*> pokemons = { new Suicune(15) };
		auto layer = BattleScene::CreateLayer(pokemons);
		layer->setPosition(lakecamera->getPosition().x - Director::getInstance()->getVisibleSize().width / 2,
			lakecamera->getPosition().y - Director::getInstance()->getVisibleSize().height / 2);
		this->addChild(layer, 1000);
		this->unscheduleUpdate();
		Buttons::GetIntance()->SetVisible(false);
		Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
	}
	return true;
}

int lakeSum = 0;

void Lake::UpdatePlayer(float dt) {
	lakeSum++;
	if (lakeSum >30) {
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
		lakeSum = 0;
	}
}

bool Lake::onTouchEnd(Touch * t, Event * event)
{
	/*this->m_messageBox->setVisible(false);
	removeChild(suicune, true);
	Buttons::GetIntance()->SetTouchEnable();*/
	return true;
}
void Lake::update(float dt)
{
	if (Model::SUICUNE == false)
	{
		suicune->removeFromParent();
	}
	for (int i = 0; i < lake_point.size(); i++)
	{
		if (this->mPlayer->GetSpriteFront()->getBoundingBox().containsPoint(lake_point.at(i)) && Buttons::state != 0 && Bag::GetInstance()->GetCountPokemon() > 0)
		{
			lake_tick += dt;
			break;
		}
	}
	if (lake_tick >= 2.5)
	{
		vector<Pokemon*> wildPokemon;
		int index = rand() % 6 + 1;
		int level = rand() % 4 + 7;
		switch (index)
		{
		case 1:
			wildPokemon.push_back(new Shaymin(level));
			break;
		case 2:
			wildPokemon.push_back(new Pidgeotto(level));
			break;
		case 3:
			wildPokemon.push_back(new Kirlia(level));
			break;
		case 4:
			wildPokemon.push_back(new Feebas(level));
			break;
		case 5:
			wildPokemon.push_back(new Dragonair(level));
			break;
		case 6:
			wildPokemon.push_back(new Meowth(level));
			break;
		default:
			break;
		}
		Buttons::GetIntance()->SetVisible(false);
		auto layer = BattleScene::CreateLayer(wildPokemon);
		layer->setPosition(lakecamera->getPosition().x - Director::getInstance()->getVisibleSize().width / 2,
			lakecamera->getPosition().y - Director::getInstance()->getVisibleSize().height / 2);
		this->addChild(layer, 1000);
		this->unscheduleUpdate();
		lake_tick = 0;
	}
	UpdatePlayer(dt);
	UpdateCamera();
	this->setTag(0);
}