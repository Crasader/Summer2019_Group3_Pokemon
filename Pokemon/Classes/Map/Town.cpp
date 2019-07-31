#include "Town.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "Lab.h"
#include "Route1.h"
#include "House.h"
#include "Model.h"
#include "Scene\BattleScene.h"
#include "Popup.h"
#include "Bag.h"
//#include "Joystick.h"
#include <cstdlib>

using namespace CocosDenshion;
USING_NS_CC;
Size townVisibleSize;
Size townTileMapSize;
TMXLayer* grass;
Sprite* tilePokemon;
PhysicsBody* pokemon;
//Joystick *joystickTown;
vector<Vec2> point;
float tick = 0;
//Layer *layer_UI;
PhysicsBody* townBody, *townGateWay;
Camera *townCamera;
int Town::previousScene = 0;

int Town::arrayGrassHasPokemon[32][16] = { 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
	 };
Scene* Town::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = Town::create();
	scene->addChild(layer);
	townCamera = scene->getDefaultCamera();
	return scene;
}

int Town::Check(int x, int y) {
	int i = 0, j = 0;
	for ( i = 0; i < 32; i++) {
		for (j = 0; j < 16; j++) {
			if ((abs(i - x) <= 2) && (abs(j - y) <= 2)) {
				if (arrayGrassHasPokemon[i][j] ==1)
					return 1;
			}
		}
	}
	return 0;
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
	auto audio = SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("res/Sound/Town.mp3", true);
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	townVisibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	map = ResourceManager::GetInstance()->GetTiledMapById(2);
	townTileMapSize = map->getContentSize();
	addChild(map);
	auto mapHouse = ResourceManager::GetInstance()->GetTiledMapById(3);
	addChild(mapHouse, 15);
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
	Button *right = Buttons::GetIntance()->GetButtonRight();
	Button *left = Buttons::GetIntance()->GetButtonLeft();
	Button *down = Buttons::GetIntance()->GetButtonDown();
	Button *bag = Buttons::GetIntance()->GetButtonBag();
	Button *tips = Buttons::GetIntance()->GetButtonTips();
	addChild(tips, 100);
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);
	addChild(bag, 100);

	//CreateLayerUI();

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
			popup->setPosition(townCamera->getPosition().x - popup->getContentSize().width / 2,
			townCamera->getPosition().y - popup->getContentSize().height / 2);
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
			popup->setPosition(townCamera->getPosition().x - popup->getContentSize().width / 2,
			townCamera->getPosition().y - popup->getContentSize().height / 2);
			this->addChild(popup, 101);
		}
	});
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(Town::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	/*auto _listener = EventListenerCustom::create(JoystickEvent::EVENT_JOYSTICK, [=](EventCustom* event) {
		JoystickEvent* jsevent = static_cast<JoystickEvent*>(event->getUserData());
		log("--------------got joystick event, %p,  angle=%f", jsevent, jsevent->mAnagle);
	}
	);*/
	scheduleUpdate();
	return true;
}

//void Town::CreateLayerUI() {
//	layer_UI = Layer::create();
//	joystickTown = Joystick::create();
//	cameraUI = Camera::create();
//	layer_UI->addChild(cameraUI, 100);
//	layer_UI->addChild(joystickTown, 100);
//	this->addChild(layer_UI, 100);
//	
//}

bool Town::onContactBegin(PhysicsContact& contact)

{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_HOUSE)
		|| (a->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_HOUSE && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		Town::previousScene = Model::PRESCENE_HOUSE_TO_TOWN;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, House::createScene()));
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
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_LAB)
		|| (a->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_LAB && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		Town::previousScene = Model::PRESCENE_LAB_TO_TOWN;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Lab::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_ROUTE1)
		|| (a->getCollisionBitmask() == Model::BITMASK_TOWN_GATE_TO_ROUTE1 && b->getCollisionBitmask() == Model::BITMASK_PLAYER))
	{
		Buttons::GetIntance()->Remove();
		Town::previousScene = Model::PRESCENE_ROUTE1_TO_TOWN;
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Route1::createScene()));
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("res/Sound/ExitRoom.mp3", false);
	}
	if ((a->getCollisionBitmask() == Model::BITMASK_WORLD && b->getCollisionBitmask() == Model::BITMASK_PLAYER)
		|| (a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_WORLD))
	{
		switch (Buttons::state)
		{
		case 1:
			mPlayer->GetSpriteFront()->stopActionByTag(0);
			mPlayer->GetSpriteFront()->setPositionY(mPlayer->GetSpriteFront()->getPositionY() - 2);
			break;
		case 2:
			mPlayer->GetSpriteFront()->stopActionByTag(6);
			mPlayer->GetSpriteFront()->setPositionX(mPlayer->GetSpriteFront()->getPositionX() - 2);
			break;
		case 3:
			mPlayer->GetSpriteFront()->stopActionByTag(4);
			mPlayer->GetSpriteFront()->setPositionX(mPlayer->GetSpriteFront()->getPositionX() + 2);
			break;
		case 4:
			mPlayer->GetSpriteFront()->stopActionByTag(2);
			mPlayer->GetSpriteFront()->setPositionY(mPlayer->GetSpriteFront()->getPositionY() + 2);
			break;
		default:
			break;
		}
	}

	return true;
}

void Town::InitObject()
{
	auto m_objectGroup = map->getObjectGroup("Object");
	auto objects = m_objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++) {
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == Model::MODLE_TYPE_MAIN_CHARACTER) {
			int preScene = object.asValueMap().at("pre").asInt();
			if (preScene == previousScene) {
				mPlayer = new Trainer(this);
				mPlayer->GetSpriteFront()->setTexture("res/Trainer/walkdown/1.png");
				mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
				townBody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
				townBody->setCollisionBitmask(Model::BITMASK_PLAYER);
				townBody->setContactTestBitmask(true);
				townBody->setDynamic(true);
				townBody->setRotationEnable(false);
				townBody->setGravityEnable(false);
				mPlayer->GetSpriteFront()->setPhysicsBody(townBody);
			}
			else continue;
		}
		else if (type == Model::MODLE_TYPE_TOWN_GATE_TO_HOUSE)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			townGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			townGateWay->setCollisionBitmask(Model::BITMASK_TOWN_GATE_TO_HOUSE);
			townGateWay->setContactTestBitmask(true);
			townGateWay->setDynamic(false);
			townGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(townGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_TOWN_GATE_TO_LAB)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			townGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			townGateWay->setCollisionBitmask(Model::BITMASK_TOWN_GATE_TO_LAB);
			townGateWay->setContactTestBitmask(true);
			townGateWay->setDynamic(false);
			townGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(townGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
		else if (type == Model::MODLE_TYPE_TOWN_GATE_TO_ROUTE1)
		{
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			townGateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			townGateWay->setCollisionBitmask(Model::BITMASK_TOWN_GATE_TO_ROUTE1);
			townGateWay->setContactTestBitmask(true);
			townGateWay->setDynamic(false);
			townGateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(townGateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void Town::UpdateCamera() {
	if (townVisibleSize.width >= townTileMapSize.width) {
		if (townVisibleSize.height >= townTileMapSize.height) {
			townCamera->setPosition(townTileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - townTileMapSize.height / 2)>abs(townTileMapSize.height / 2 - townVisibleSize.height / 2)) {
				townCamera->setPosition(townTileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().y) ? (townTileMapSize.height - townVisibleSize.height / 2) : townVisibleSize.height / 2);
			}
			else {
				townCamera->setPosition(townTileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (townVisibleSize.height >= townTileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - townTileMapSize.width / 2)>abs(townTileMapSize.width / 2 - townVisibleSize.width / 2)) {
				townCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().y) ? (townTileMapSize.width - townVisibleSize.width / 2) : townVisibleSize.width / 2, townTileMapSize.height / 2);
			}
			else {
				townCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, townTileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - townTileMapSize.width / 2)>abs(townTileMapSize.width / 2 - townVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - townTileMapSize.height / 2)>abs(townTileMapSize.height / 2 - townVisibleSize.height / 2)) {
				townCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >townCamera->getPosition().x) ? (townTileMapSize.width - townVisibleSize.width / 2) : townVisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().y) ? (townTileMapSize.height - townVisibleSize.height / 2) : townVisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - townTileMapSize.width / 2)>abs(townTileMapSize.width / 2 - townVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - townTileMapSize.height / 2)<abs(townTileMapSize.height / 2 - townVisibleSize.height / 2)) {
				townCamera->setPosition((mPlayer->GetSpriteFront()->getPosition().x >townCamera->getPosition().x) ? (townTileMapSize.width - townVisibleSize.width / 2) : townVisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - townTileMapSize.width / 2)<abs(townTileMapSize.width / 2 - townVisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - townTileMapSize.height / 2)>abs(townTileMapSize.height / 2 - townVisibleSize.height / 2)) {
				townCamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >townCamera->getPosition().y) ? (townTileMapSize.height - townVisibleSize.height / 2) : townVisibleSize.height / 2);
			}
			else {
				townCamera->setPosition(mPlayer->GetSpriteFront()->getPosition());
			}
		}
	}
}

//void Town::InitArray()
//{
//	for (int i = 0; i < 32; i++) {
//		for (int j = 0; j < 32; j++) {
//			arrayOfTile[i][j] = 0;
//		}
//	}
//}

void Town::InitGrass()
{
	grass = map->getLayer("grass");
	int width = grass->getLayerSize().width;
	int height = grass->getLayerSize().height;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			tilePokemon = grass->getTileAt(Vec2(i, j));
			if (tilePokemon != NULL)
			{
				point.push_back(tilePokemon->getPosition());
			}
		}
	}
}

void Town::update(float dt)
{
	for (int i = 0; i < point.size(); i++)
	{
		if (this->mPlayer->GetSpriteFront()->getBoundingBox().containsPoint(point.at(i)) && Buttons::state != 0)
		{
			tick += dt;
			break;
		}
	}
	if (tick >= 2.5)
	{
		vector<Pokemon*> wildPokemon;
		int index = rand() % 6 + 1;
		switch (index)
		{
		case 1:
			wildPokemon.push_back(new Meowth());
			break;
		case 2:
			wildPokemon.push_back(new Ralts());
			break;
		case 3:
			wildPokemon.push_back(new Pikachu());
			break;
		case 4:
			wildPokemon.push_back(new Pidgey());
			break;
		case 5:
			wildPokemon.push_back(new Taillow());
			break;
		case 6:
			wildPokemon.push_back(new Farfetchd());
			break;
		default:
			break;
		}
		Buttons::GetIntance()->SetEnabled(false);
		auto layer = BattleScene::CreateLayer(wildPokemon);
		this->addChild(layer, 1000);
		this->unscheduleUpdate();
		tick = 0;
	}
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(townCamera->getPosition().x - 200, townCamera->getPosition().y - 100);
}