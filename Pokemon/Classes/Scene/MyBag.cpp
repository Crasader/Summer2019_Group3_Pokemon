#include "MyBag.h"
#include "ui\UITabControl.h"

cocos2d::Scene * MyBag::createScene()
{
	auto scene = Scene::create();
	auto layer = MyBag::create();
	scene->addChild(layer);
	return scene;
}

bool MyBag::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto tab = TabControl::create();
	tab->setContentSize(Size(500.0f, 200.f));
	tab->setHeaderHeight(40.f);
	tab->setHeaderWidth(70.f);
	tab->setHeaderSelectedZoom(.1f);
	tab->setHeaderDockPlace(TabControl::Dock::TOP);

	auto header1 = TabHeader::create();
	header1->setTitleText("My Pokemon");
	header1->loadTextureBackGround("res/Button/ButtonPlay.png");
	auto header2 = TabHeader::create();
	header2->setTitleText("My Item");
	header2->loadTextureBackGround("res/Button/ButtonPlay.png");

	auto container1 = Layout::create();
	container1->setOpacity(255);
	container1->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	container1->setBackGroundColor(Color3B::GRAY);
	container1->setBackGroundColorOpacity(255);
	auto container2 = Layout::create();
	container2->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	container2->setOpacity(255);
	container2->setBackGroundColor(Color3B::BLUE);
	container2->setBackGroundColorOpacity(255);

	tab->insertTab(0, header1, container1);
	tab->insertTab(1, header2, container2);

	tab->setSelectTab(0);
	addChild(tab);
	tab->setPosition(Vec2(visibleSize.width * .5f, visibleSize.height * .5f));
	return true;
}

void MyBag::update(float deltaTime)
{
}
