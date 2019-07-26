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
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void UpdateCamera();
    CREATE_FUNC(PokemonCenter);
	void update(float);
};

#endif // __PokemonCenter_SCENE_H__