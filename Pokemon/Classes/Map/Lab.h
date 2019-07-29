#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include <math.h>
using namespace cocos2d;
using namespace std;
class Lab : public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;
	Sprite * m_doctor;
	Label* m_labelLog;
	Sprite* m_messageBox;
	int writing = 0;
	bool m_stateLog = false;
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void TypeWriter(float deltaTime);
	void LogSetOpacity(GLubyte opacity);
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void UpdateCamera();
	void Log(string logg);
	bool onTouchBegan(Touch* touch, Event* e);
	//void CreateButon();
	CREATE_FUNC(Lab);
	//void createPhysics();
	void update(float);
};