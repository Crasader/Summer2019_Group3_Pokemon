#ifndef __LAKE_H__
#define __LAKE_H__

#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include <math.h>
using namespace cocos2d;
using namespace std;
class Lake: public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;
	Sprite * suicune;
	Label* m_labelLog;
	Sprite* m_messageBox;
	int writing = 0;
	bool m_stateLog = false;
public:
    static cocos2d::Scene* createScene();
	void TypeWriter(float deltaTime);
	void LogSetOpacity(GLubyte opacity);
    virtual bool init();
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void UpdateCamera();
	void Log(string logg);
	bool onTouchBegan(Touch* touch, Event* e);
	//void CreateButon();
    CREATE_FUNC(Lake);
	//void createPhysics();
	void update(float);
};
#endif