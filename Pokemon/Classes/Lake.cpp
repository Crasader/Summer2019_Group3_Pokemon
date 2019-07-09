
#include "Lake.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Pokemon\Charmander.h"
#include "Pokemon\Squirtle.h"
#include "Buttons.h"
USING_NS_CC;

Scene* Lake::createScene()
{
	auto scene = Scene::create();
	auto layer = Lake::create();
	scene->addChild(layer);
	return scene;
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
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto map = TMXTiledMap::create("res/Map/lake.tmx");
	addChild(map);
	
	/*auto m_objectGroup = map->getObjectGroup("Object");
	auto objects = m_objectGroup->getObjects();
	auto object = objects.at(0);
	auto properties = object.asValueMap();
	int posX = properties.at("x").asInt();
	int posY = properties.at("y").asInt();
	int type = object.asValueMap().at("type").asInt();
	mPlayer = new Trainer(this);
	*/

	Button *up = Buttons::getIntance()->GetButtonUp();
	up->removeFromParent();
	Button *right = Buttons::getIntance()->GetButtonRight();
	right->removeFromParent();
	Button *left = Buttons::getIntance()->GetButtonLeft();
	left->removeFromParent();
	Button *down = Buttons::getIntance()->GetButtonDown();
	down->removeFromParent();
	addChild(up, 100);
	addChild(right, 100);
	addChild(left, 100);
	addChild(down, 100);
	/*up->addClickEventListener([&](Ref* event) {
		object->setPosition(getPosition().x , getPosition().y + 10);
	});
	right->addClickEventListener([&](Ref* event) {
		object->setPosition(getPosition().x + 10, getPosition().y );

	});
	left->addClickEventListener([&](Ref* event) {
		object->setPosition(getPosition().x - 10, getPosition().y);

	});
	down->addClickEventListener([&](Ref* event) {
		object->setPosition(getPosition().x , getPosition().y - 10);

	});*/
    return true;
}

