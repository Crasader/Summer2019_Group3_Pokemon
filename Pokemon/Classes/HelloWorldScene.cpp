
#include "HelloWorldScene.h"
#include "ResourceManager.h"
#include "SimpleAudioEngine.h"
#include "ResourceManager.h"
#include "Pokemon\Charmander.h"
#include "Pokemon\Squirtle.h"

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
	auto scale_x = visibleSize.width / tiledmap->getContentSize().width;
	auto scale_y = visibleSize.height / tiledmap->getContentSize().height;
	tiledmap->setScaleX(scale_x);
	tiledmap->setScaleY(scale_y);
	this->addChild(tiledmap, -10);
	auto obj = tiledmap->getObjectGroup("pokemon");
	auto opp = obj->getObject("opponent");
	auto x = opp["x"].asFloat() * scale_x;
	auto y = opp["y"].asFloat() * scale_y;
	auto player = obj->getObject("player");
	auto m_x = player["x"].asFloat() * scale_x;
	auto m_y = player["y"].asFloat() * scale_y;

	Pokemon* charmander = new Charmander();
	charmander->GetSpriteFront()->setPosition(Vec2(x, y));
	this->addChild(charmander->GetSpriteFront(), 10);
	Pokemon* squirtle = new Squirtle();
	auto evolve = squirtle->Evolve();
	if (evolve != nullptr)
	{
		squirtle = evolve;
	}
	squirtle->GetSpriteBack()->setPosition(Vec2(m_x, m_y));
	this->addChild(squirtle->GetSpriteBack(), 10);

	auto btn_1 = ResourceManager::GetInstance()->GetButtonById(5);
	btn_1->setAnchorPoint(Vec2(1, 0.5));
	btn_1->setPosition(Vec2(visibleSize.width, btn_1->getContentSize().height * 4));
	auto lb_1 = ResourceManager::GetInstance()->GetLabelById(0);
	lb_1->setString("Fight");
	lb_1->setTag(0);
	lb_1->setPosition(btn_1->getContentSize().width / 2, btn_1->getContentSize().height / 2);
	btn_1->addChild(lb_1);
	addChild(btn_1);
	auto btn_2 = ResourceManager::GetInstance()->GetButtonById(5);
	btn_2->setAnchorPoint(Vec2(1, 0.5));
	btn_2->setPosition(Vec2(visibleSize.width, btn_2->getContentSize().height * 2.9));
	auto lb_2 = ResourceManager::GetInstance()->GetLabelById(0);
	lb_2->setString("Bag");
	lb_2->setTag(1);
	lb_2->setPosition(btn_2->getContentSize().width / 2, btn_2->getContentSize().height / 2);
	btn_2->addChild(lb_2);
	addChild(btn_2);
	auto btn_3 = ResourceManager::GetInstance()->GetButtonById(5);
	btn_3->setAnchorPoint(Vec2(1, 0.5));
	btn_3->setPosition(Vec2(visibleSize.width, btn_3->getContentSize().height * 1.8));
	auto lb_3 = ResourceManager::GetInstance()->GetLabelById(0);
	lb_3->setString("Pokemon");
	lb_3->setTag(2);
	lb_3->setPosition(btn_3->getContentSize().width / 2, btn_3->getContentSize().height / 2);
	btn_3->addChild(lb_3);
	addChild(btn_3);
	auto btn_4 = ResourceManager::GetInstance()->GetButtonById(5);
	btn_4->setAnchorPoint(Vec2(1, 0.5));
	btn_4->setPosition(Vec2(visibleSize.width, btn_4->getContentSize().height*0.7));
	auto lb_4 = ResourceManager::GetInstance()->GetLabelById(0);
	lb_4->setString("Run");
	lb_4->setTag(4);
	lb_4->setPosition(btn_4->getContentSize().width / 2, btn_4->getContentSize().height / 2);
	btn_4->addChild(lb_4);
	addChild(btn_4);
	btn_1->addTouchEventListener([lb_1,lb_2,lb_3,lb_4,squirtle](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::BEGAN:
			break;
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			if (lb_1->getString() == "Fight")
			{
				//lb_1->setString(squirtle->GetListSkill().at(0)->GetName());
				//lb_2->setString(squirtle->GetListSkill().at(1)->GetName());
				lb_3->setString("-");
				lb_4->setString("Back");
			}
			break;
		default:
			break;
		}
	});

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
