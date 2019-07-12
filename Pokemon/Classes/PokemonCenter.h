#ifndef __POKEMONCENTER_H__
#define __POKEMONCENTER_H__

#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
USING_NS_CC;
class PokemonCenter : public cocos2d::Layer
{
private:
	Trainer *mPlayer;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(PokemonCenter);
};

#endif // __PokemonCenter_SCENE_H__