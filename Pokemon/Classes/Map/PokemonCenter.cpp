
#include "PokemonCenter.h"
#include "ResourceManager.h"
#include "Buttons.h"
#include "Lake.h"

USING_NS_CC;
Size PcvisibleSize;
Size PctileMapSize;

PhysicsBody* Pcbody, *PcgateWay;
Camera *Pccamera;

Scene* PokemonCenter::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = PokemonCenter::create();
	scene->addChild(layer);
	Pccamera = scene->getDefaultCamera();
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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	PcvisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/pc.tmx");
	PctileMapSize = map->getContentSize();
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

	if (a->getCollisionBitmask() == 15 && b->getCollisionBitmask() == 17
		|| a->getCollisionBitmask() == 17 && b->getCollisionBitmask() == 15)
	{
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Lake::createScene()));
	}

	return true;

}

void PokemonCenter::InitObject()
{
	auto map = TMXTiledMap::create("res/Map/pc.tmx");
	auto m_objectGroup = map->getObjectGroup("Object");
	auto objects = m_objectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++) {
		auto object = objects.at(i);
		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();
		if (type == 1) {
			mPlayer = new Trainer(this);
			mPlayer->GetSpriteFront()->setPosition(Vec2(posX, posY));
			Pcbody = PhysicsBody::createBox(mPlayer->GetSpriteFront()->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			Pcbody->setCollisionBitmask(17);
			Pcbody->setMass(16);
			Pcbody->setContactTestBitmask(true);
			Pcbody->setDynamic(true);
			Pcbody->setRotationEnable(false);
			Pcbody->setGravityEnable(false);
			mPlayer->GetSpriteFront()->setPhysicsBody(Pcbody);
		}
		else {
			mGateWay = Sprite::create("res/walkup.png");
			mGateWay->setPosition(Vec2(posX, posY));
			PcgateWay = PhysicsBody::createBox(mGateWay->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
			PcgateWay->setCollisionBitmask(15);
			PcgateWay->setMass(14);
			PcgateWay->setContactTestBitmask(true);
			PcgateWay->setDynamic(false);
			PcgateWay->setGravityEnable(false);
			mGateWay->setPhysicsBody(PcgateWay);
			mGateWay->setVisible(false);
			this->addChild(mGateWay, 10);
		}
	}

}

void PokemonCenter::updateCamera()
{
	if (PcvisibleSize.width >= PctileMapSize.width) {
		if (PcvisibleSize.height >= PctileMapSize.height) {
			Pccamera->setPosition(PctileMapSize / 2);
		}
		else
		{
			if (abs(mPlayer->GetSpriteFront()->getPosition().y - PctileMapSize.height / 2)>abs(PctileMapSize.height / 2 - PcvisibleSize.height / 2)) {
				Pccamera->setPosition(PctileMapSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Pccamera->getPosition().y) ? (PctileMapSize.height - PcvisibleSize.height / 2) : PcvisibleSize.height / 2);
			}
			else {
				Pccamera->setPosition(PctileMapSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
		}
	}
	else {
		if (PcvisibleSize.height >= PctileMapSize.height) {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - PctileMapSize.width / 2)>abs(PctileMapSize.width / 2 - PcvisibleSize.width / 2)) {
				Pccamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Pccamera->getPosition().y) ? (PctileMapSize.width - PcvisibleSize.width / 2) : PcvisibleSize.width / 2, PctileMapSize.height / 2);
			}
			else {
				Pccamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, PctileMapSize.height / 2);
			}
		}
		else {
			if (abs(mPlayer->GetSpriteFront()->getPosition().x - PctileMapSize.width / 2)>abs(PctileMapSize.width / 2 - PcvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - PctileMapSize.height / 2)>abs(PctileMapSize.height / 2 - PcvisibleSize.height / 2)) {
				Pccamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Pccamera->getPosition().x) ? (PctileMapSize.width - PcvisibleSize.width / 2) : PcvisibleSize.width / 2, (mPlayer->GetSpriteFront()->getPosition().y >Pccamera->getPosition().y) ? (PctileMapSize.height - PcvisibleSize.height / 2) : PcvisibleSize.height / 2);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - PctileMapSize.width / 2)>abs(PctileMapSize.width / 2 - PcvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - PctileMapSize.height / 2)<abs(PctileMapSize.height / 2 - PcvisibleSize.height / 2)) {
				Pccamera->setPosition((mPlayer->GetSpriteFront()->getPosition().y >Pccamera->getPosition().x) ? (PctileMapSize.width - PcvisibleSize.width / 2) : PcvisibleSize.width / 2, mPlayer->GetSpriteFront()->getPosition().y);
			}
			else if (abs(mPlayer->GetSpriteFront()->getPosition().x - PctileMapSize.width / 2)<abs(PctileMapSize.width / 2 - PcvisibleSize.width / 2)
				&& abs(mPlayer->GetSpriteFront()->getPosition().y - PctileMapSize.height / 2)>abs(PctileMapSize.height / 2 - PcvisibleSize.height / 2)) {
				Pccamera->setPosition(mPlayer->GetSpriteFront()->getPosition().x, (mPlayer->GetSpriteFront()->getPosition().y >Pccamera->getPosition().y) ? (PctileMapSize.height - PcvisibleSize.height / 2) : PcvisibleSize.height / 2);
			}
			else {
				Pccamera->setPosition(mPlayer->GetSpriteFront()->getPosition() / 2);
			}
		}
	}

}
void PokemonCenter::update(float dt)
{
	updateCamera();
	Buttons::GetIntance()->UpdateButton(Pccamera->getPosition().x - 200, Pccamera->getPosition().y - 100);
}

