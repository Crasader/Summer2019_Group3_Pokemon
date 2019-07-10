
#include "Lake.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Pokemon\Charmander.h"
#include "Pokemon\Squirtle.h"
#include "Buttons.h"

USING_NS_CC;
int state_up = 0;
int state_right = 0;
int state_left  = 0;
int state_down = 0;

Button *up;
Button *down;
Button *left1;
Button *right1;

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
	
	auto m_objectGroup = map->getObjectGroup("Object");
	auto objects = m_objectGroup->getObjects();
	auto object = objects.at(0);
	auto properties = object.asValueMap();
	int posX = properties.at("x").asInt();
	int posY = properties.at("y").asInt();
	int type = object.asValueMap().at("type").asInt();
	mPlayer = new Trainer(this);
	mPlayer->setPosition(Vec2(posX, posY));
	mPlayer->setScale(0.1f);

	up = Buttons::getIntance()->GetButtonUp();
	up->removeFromParent();

	right1 = Buttons::getIntance()->GetButtonRight();
	right1->removeFromParent();

	left1 = Buttons::getIntance()->GetButtonLeft();
	left1->removeFromParent();

	down = Buttons::getIntance()->GetButtonDown();
	down->removeFromParent();

	addChild(up, 100);
	addChild(right1, 100);
	addChild(left1, 100);
	addChild(down, 100);
	up->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			state_up = 1;
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			state_up = 0;
			break;
		}
		default:
			break;
		}
	});


	right1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			state_right = 1;
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			state_right = 0;
			break;
		}
		default:
		{
			state_right = 0;
			break;
		}

		}
	});
	left1->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			state_left = 1;
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			state_left = 0;
			break;
		}
		default:
			break;
		}
	});
	down->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
		{
			state_down = 1;
			break;
		}
		case ui::Widget::TouchEventType::ENDED:
		{
			state_down = 0;
			break;
		}
		default:
			break;
		}
	});
	scheduleUpdate();
    return true;
}
float total = 0;
void Lake::update(float dt) {
	total += dt;
	if (total = 0.3f) {
		if (state_up) {
			mPlayer->walkUp();
		}
		if (state_down) {
			mPlayer->walkDown();
		}
		if (state_left) {
			mPlayer->walkLeft();
		}
		if (state_right) {
			mPlayer->walkRight();
		}
		total = 0;
		auto followTheSprite = Follow::create(mPlayer->GetSprite(), Rect::ZERO);
		this->runAction(followTheSprite);
	}
}