#ifndef __ROUTE1_H__
#define __ROUTE1_H__

#include "cocos2d.h"
#include "Pokemon.h"

class Route1 : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(Route1);
};

#endif