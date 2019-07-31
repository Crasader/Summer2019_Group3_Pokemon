#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include "NPC\CaveNPC.h"
#include "NPC\LakeNPC.h"
#include "NPC\Route2NPC.h"
#include <math.h>
using namespace cocos2d;
using namespace std;
class City : public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;
	CaveNPC * m_cavenpc;
	LakeNPC * m_lakenpc;
	Route2NPC * m_route2npc;
	EventListenerTouchOneByOne* touchListener;
	Label* m_labelLog;
	Sprite* m_messageBox;
	int writing = 0;
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
	bool onTouchEnd(Touch* t, Event* event);
	//void CreateButon();
	CREATE_FUNC(City);
	void UpdatePlayer(float dt);
	//void createPhysics();
	void update(float);
};