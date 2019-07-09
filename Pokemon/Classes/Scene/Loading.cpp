#include "Scene\Loading.h"
#include "ResourceManager.h"

using namespace cocos2d;
using namespace std;

Scene* Loading::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
	auto layer = Loading::create();
	scene->addChild(layer);
	return scene;
}

bool Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	return true;
}
