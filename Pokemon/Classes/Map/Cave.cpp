#include "Cave.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "Buttons.h"
#include "City.h"
#include "Model.h"
#include "Scene\BattleScene.h"
#include "Popup.h"
using namespace CocosDenshion;
USING_NS_CC;

Size caveVisibleSize;
Size caveTileMapSize;

vector<Vec2> cave_point;
float cave_tick = 0;

Layer *layer_UI_Cave;
PhysicsBody* caveBody, *caveGateWay, *enteiBody;
Camera *caveCamera, *cameraUICave;

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

	map = TMXTiledMap::create("res/Map/Cave.tmx");
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
	Button *bag = Buttons::GetIntance()->GetButtonBag();
	Button *tips = Buttons::GetIntance()->GetButtonTips();

	layer_UI_Cave = Layer::create();
	cameraUICave = Camera::create();
	cameraUICave->setCameraMask(2);
	cameraUICave->setCameraFlag(CameraFlag::USER1);
	up->setCameraMask(2);
	bag->setCameraMask(2);
	tips->setCameraMask(2);
	layer_UI_Cave->addChild(cameraUICave, 2);
	layer_UI_Cave->addChild(up);
	layer_UI_Cave->addChild(bag);
	layer_UI_Cave->addChild(tips);
	this->addChild(layer_UI_Cave, 100);

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
			popup->setPosition(caveCamera->getPosition().x - popup->getContentSize().width / 2,
				caveCamera->getPosition().y - popup->getContentSize().height / 2);
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
			popup->setPosition(caveCamera->getPosition().x - popup->getContentSize().width / 2,
				caveCamera->getPosition().y - popup->getContentSize().height / 2);
			this->addChild(popup, 101);
		}
	});

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
	this->addChild(this->m_messageBox, 10);
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
	else if ((a->getCollisionBitmask() == Model::BITMASK_PLAYER && b->getCollisionBitmask() == Model::BITMASK_ENTEI && Bag::GetInstance()->GetCountPokemon() > 0)
		|| a->getCollisionBitmask() == Model::BITMASK_ENTEI && b->getCollisionBitmask() == Model::BITMASK_PLAYER && Bag::GetInstance()->GetCountPokemon() > 0)
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
		Buttons::GetIntance()->SetVisible(false);
		this->Log("Enteiiiiii!");
		this->m_messageBox->setVisible(true);
		touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Cave::onTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
		auto listener = CallFunc::create([this]() {
			if (this->getTag() == 10)
			{
				Model::ENTEI = false;
				this->stopActionByTag(100);
			}
		});
		auto rp = RepeatForever::create(Spawn::create(listener, nullptr));
		rp->setTag(100);
		this->runAction(rp);
	}
	return true;
}

void Cave::InitGrass()
{
	auto grass = map->getLayer("ground");
	int width = grass->getLayerSize().width;
	int height = grass->getLayerSize().height;
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			auto tilePokemon = grass->getTileAt(Vec2(i, j));
			if (tilePokemon != NULL)
			{
				cave_point.push_back(tilePokemon->getPosition());
			}
		}
	}
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
				entei = ResourceManager::GetInstance()->GetSpriteById(149);
				entei->setPosition(Vec2(posX, posY));
				entei->setScale(2);
				enteiBody = PhysicsBody::createBox(entei->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
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
	audio->playEffect("res/Sound/Beep.mp3", false);
	this->m_labelLog->setString(logg);
	this->LogSetOpacity(0);
	this->m_labelLog->setOpacity(0);
	writing = 0;
	this->schedule(schedule_selector(Cave::TypeWriter), 0.05);
}

bool Cave::onTouchBegan(Touch * touch, Event * e)
{
	if (this->m_labelLog->getOpacity() == 0)
	{
		this->unschedule(schedule_selector(Cave::TypeWriter));
		this->LogSetOpacity(255);
		this->m_labelLog->setOpacity(255);
		/*auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Cave::onTouchEnd, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);*/
	}
	else
	{
		this->m_messageBox->setVisible(false);
		vector<Pokemon*> pokemons = { new Entei(15) };
		auto layer = BattleScene::CreateLayer(pokemons);
		layer->setPosition(caveCamera->getPosition().x - Director::getInstance()->getVisibleSize().width / 2,
			caveCamera->getPosition().y - Director::getInstance()->getVisibleSize().height / 2);
		this->addChild(layer, 1000);
		this->unscheduleUpdate();
		//Buttons::GetIntance()->SetVisible(false);
		Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
	}
	return true;
}

int caveSum = 0;

void Cave::UpdatePlayer(float dt) {
	caveSum++;
	if (caveSum >30) {
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
		caveSum = 0;
	}
}

bool Cave::onTouchEnd(Touch * t, Event * event)
{
	/*removeChild(entei, true);
	this->m_messageBox->setVisible(false);
	Buttons::GetIntance()->SetTouchEnable();*/
	return true;
}

void Cave::update(float dt)
{
	if (Model::ENTEI == false)
	{
		entei->removeFromParent();
	}
	for (int i = 0; i < cave_point.size(); i++)
	{
		if (this->mPlayer->GetSpriteFront()->getBoundingBox().containsPoint(cave_point.at(i)) && Buttons::state != 0 && Bag::GetInstance()->GetCountPokemon() > 0)
		{
			cave_tick += dt;
			break;
		}
	}
	if (cave_tick >= 2.5)
	{
		vector<Pokemon*> wildPokemon;
		int index = rand() % 5 + 1;
		int level = rand() % 4 + 7;
		switch (index)
		{
		case 1:
			wildPokemon.push_back(new Voltorb(level));
			break;
		case 2:
			wildPokemon.push_back(new Garchomp(level));
			break;
		case 3:
			wildPokemon.push_back(new Manectric(level));
			break;
		case 4:
			wildPokemon.push_back(new Ponyta(level));
			break;
		case 5:
			wildPokemon.push_back(new Meowth(level));
			break;
		default:
			break;
		}
		Buttons::GetIntance()->SetVisible(false);
		auto layer = BattleScene::CreateLayer(wildPokemon);
		layer->setPosition(caveCamera->getPosition().x - Director::getInstance()->getVisibleSize().width / 2,
			caveCamera->getPosition().y - Director::getInstance()->getVisibleSize().height / 2);
		this->addChild(layer, 1000);
		this->unscheduleUpdate();
		cave_tick = 0;
	}
	UpdatePlayer(dt);
	UpdateCamera();
	this->setTag(0);
}
