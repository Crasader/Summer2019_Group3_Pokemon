#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include <math.h>
using namespace cocos2d;
using namespace std;
class Route2 : public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;
	Sprite * m_raikou;
	Sprite * m_roadnpc;
	Label* m_labelLog;
	Sprite* m_messageBox;
	int writing = 0;
	bool m_stateLog = false;
public:
	static cocos2d::Scene* createScene();
	static int previousScene;
	void TypeWriter(float deltaTime);
	void LogSetOpacity(GLubyte opacity);
	virtual bool init();
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void UpdateCamera();
	void Log(string logg);
	bool onTouchBegan(Touch* touch, Event* e);
	//void CreateButon();
	CREATE_FUNC(Route2);
	//void createPhysics();
	void update(float);
};