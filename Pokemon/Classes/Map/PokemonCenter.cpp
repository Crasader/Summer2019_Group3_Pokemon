
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

PhysicsBody* pcbody, *pcgateWay;
Camera *pccamera;

Scene* PokemonCenter::createScene()
{
	auto scene = Scene::createWithPhysics();
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
	audio->playBackgroundMusic("res/Sound/PokemonCenter.mp3", true);
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	pcvisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	auto map = ResourceManager::GetInstance()->GetTiledMapById(8);
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
				physics->setCollisionBitmask(13);
				physics->setContactTestBitmask(true);
				physics->setDynamic(false);
				physics->setGravityEnable(false);
				physics->setMass(12);
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
	return true;
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
	}

	return true;

}

void PokemonCenter::InitObject()
{
	auto map = ResourceManager::GetInstance()->GetTiledMapById(8);
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
void PokemonCenter::update(float dt)
{
	UpdateCamera();
	Buttons::GetIntance()->UpdateButton(pccamera->getPosition().x - 200, pccamera->getPosition().y - 100);
}