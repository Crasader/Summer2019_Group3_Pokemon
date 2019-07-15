#ifndef __BUYITEM_SCENE_H__
#define __BUYITEM_SCENE_H__

#include "cocos2d.h"
#include "Pokemon.h"

using namespace cocos2d;

class BuyItem : public Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	void update(float deltaTime) override;

	CREATE_FUNC(BuyItem);

};
#endif