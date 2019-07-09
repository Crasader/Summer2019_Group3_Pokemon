
#include "HelloWorldScene.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Pokemon\Charmander.h"
#include "Pokemon\Squirtle.h"
#include "NPC.h"
#include "NPC\CityNPC.h"




USING_NS_CC;

Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	auto layer = HelloWorld::create();
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
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto tiledmap = ResourceManager::GetInstance()->GetTiledMapById(0);
	this->addChild(tiledmap, -10);
	auto obj = tiledmap->getObjectGroup("pokemon");
	auto opp = obj->getObject("opponent");
	auto x = opp["x"].asFloat();
	auto y = opp["y"].asFloat();
	auto player = obj->getObject("player");
	auto m_x = player["x"].asFloat();
	auto m_y = player["y"].asFloat();

	Pokemon* charmander = new Charmander();
	charmander->GetSpriteFront()->setPosition(Vec2(x, y));
	this->addChild(charmander->GetSpriteFront(), 10);
	Pokemon* squirtle = new Squirtle();
	squirtle->GetSpriteBack()->setPosition(Vec2(m_x, m_y));
	this->addChild(squirtle->GetSpriteBack(), 10);

	
	NPC* testnpc = new CityNPC(this);
	int i = testnpc->GetVector().at(0)->GetLevel();
	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
