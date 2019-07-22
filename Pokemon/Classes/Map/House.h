
#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include <math.h>
using namespace cocos2d;
using namespace std;
class House : public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void updateCamera();
	//void CreateButon();
	CREATE_FUNC(House);
	//void createPhysics();
	void update(float);
};