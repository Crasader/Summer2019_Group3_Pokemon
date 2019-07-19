#include "Loading.h"
#include "MainMenu.h"
#include "ResourceManager.h"

using namespace cocos2d;
using namespace std;

Scene* Loading::createScene()
{
	auto scene = Scene::create();
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

	backGround = ResourceManager::GetInstance()->GetSpriteById(133);
	backGround->removeFromParent();
	backGround->setAnchorPoint(Vec2(0, 0));
	backGround->setScale(visibleSize.width / backGround->getContentSize().width, visibleSize.height / backGround->getContentSize().height);
	addChild(backGround, -99);

	loadingBar = ResourceManager::GetInstance()->GetSpriteById(135);
	loadingBar->setScaleX(visibleSize.width / (3*loadingBar->getContentSize().width));
	loadingBar->setAnchorPoint(Vec2(0, 0.5));
	loadingBar->setPosition(visibleSize.width / 3, visibleSize.height / 9);
	addChild(loadingBar);

	progress = ResourceManager::GetInstance()->GetSpriteById(136);
	progress->setScaleX(visibleSize.width / (300*loadingBar->getContentSize().width));
	progress->setPosition(visibleSize.width / 3, visibleSize.height / 9);
	progress->setAnchorPoint(Vec2(0, 0.5f));
	addChild(progress);

	auto scale = ScaleBy::create(3, 100.0f, 1.0f);
	progress->runAction(scale);

	scheduleUpdate();
	return true;
}
void Loading::update(float deltaTime)
{
	static float temp;
	temp += deltaTime;
	if (temp > 3.0f) // 3s - 60fps/1s
	{
		Director::getInstance()->getRunningScene()->pause();
		Director::getInstance()->replaceScene(MainMenu::createScene());
		backGround->release();
		loadingBar->release();
		progress->release();
	}
}
