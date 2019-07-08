#ifndef __TESTMAP_SCENE_H__
#define __TESTMAP_SCENE_H__

#include "cocos2d.h"
#include "Pokemon.h"

class TestMap : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(TestMap);
};

#endif // __TESTMAP_SCENE_H__