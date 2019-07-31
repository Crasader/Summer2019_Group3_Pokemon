#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include <math.h>
using namespace cocos2d;
using namespace std;
class Town : public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;
	TMXTiledMap* map;
public:
	static cocos2d::Scene* createScene();
	static int previousScene;
	virtual bool init();
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void UpdateCamera();
	void InitGrass();
	//void CreateButon();
	CREATE_FUNC(Town);
	//void createPhysics();
	void update(float dt);
};