#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "cocos2d.h"
#include "Pokemon.h"
using namespace cocos2d;

class Loading : public Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;
	void update(float deltaTime) override;

	CREATE_FUNC(Loading);

};
#endif