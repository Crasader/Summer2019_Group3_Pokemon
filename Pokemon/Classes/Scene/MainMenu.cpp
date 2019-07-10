#include "Scene\MainMenu.h"
#include "ResourceManager.h"
#include "NPC\LakeNPC.h"

using namespace cocos2d;
using namespace std;

Scene* MainMenu::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer = MainMenu::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backGround = ResourceManager::GetInstance()->GetSpriteById(101);
	backGround->removeFromParent();
	backGround->setAnchorPoint(Vec2(0, 0));
	backGround->setScale(visibleSize.width / backGround->getContentSize().width, visibleSize.height / backGround->getContentSize().height);
	addChild(backGround, -99);

	return true;
}