#ifndef __LAKE_H__
#define __LAKE_H__

#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
using namespace cocos2d;
using namespace std;
class Lake: public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void InitObject();
	void CreateButon();
	void ButtonListener();
    CREATE_FUNC(Lake);
	void createPhysics();
	void update(float);
	void onKeyPressed(EventKeyboard::KeyCode, Event*);
	void onKeyReleased(EventKeyboard::KeyCode, Event*);
};

#endif