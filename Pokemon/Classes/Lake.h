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
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(Lake);
	void update(float);
};

#endif