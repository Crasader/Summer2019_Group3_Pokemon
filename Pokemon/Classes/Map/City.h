#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include <math.h>
using namespace cocos2d;
using namespace std;
class City : public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;
public:
	static cocos2d::Scene* createScene();
	static int previousScene;
	virtual bool init();
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void UpdateCamera();
	//void CreateButon();
	CREATE_FUNC(City);
	void UpdatePlayer(float dt);
	//void createPhysics();
	void update(float);
};