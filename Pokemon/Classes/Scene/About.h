#ifndef __ABOUT_SCENE_H__
#define __ABOUT_SCENE_H__

#include "cocos2d.h"
#include "Pokemon.h"
using namespace cocos2d;
using namespace std;

class About : public Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init() override;

	CREATE_FUNC(About);
	void showEndGamePopup();
};
#endif
