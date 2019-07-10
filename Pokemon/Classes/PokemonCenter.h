#ifndef __POKEMONCENTER_H__
#define __POKEMONCENTER_H__

#include "cocos2d.h"
#include "Pokemon.h"

class PokemonCenter : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(PokemonCenter);
};

#endif // __PokemonCenter_SCENE_H__