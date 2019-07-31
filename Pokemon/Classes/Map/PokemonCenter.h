#ifndef __POKEMONCENTER_H__
#define __POKEMONCENTER_H__

#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include <math.h>
USING_NS_CC;
class PokemonCenter : public cocos2d::Layer
{
private:
	Trainer *mPlayer;
	Sprite * mGateWay;
	Sprite * m_nurse;
	Sprite * m_shop;
	Label* m_labelLog;
	Sprite* m_messageBox;
	int writing = 0;
public:
    static cocos2d::Scene* createScene();
	static int previousScene;
    virtual bool init();
	void TypeWriter(float deltaTime);
	void LogSetOpacity(GLubyte opacity);
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void UpdateCamera();
	void Log(string logg);
	bool onTouchBegan(Touch* touch, Event* e);
	bool onTouchEnd(Touch* t, Event* event);
    CREATE_FUNC(PokemonCenter);
	void UpdatePlayer(float dt);
	void update(float);
};

#endif // __PokemonCenter_SCENE_H__