#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "Pokemon.h"
using namespace cocos2d;
using namespace std;

class MainMenu : public Layer
{
private:
	Sprite* backGround;
	Button* buttonPlay;
	Button* buttonSetting;
	Button* buttonAbout;
	Button* buttonExit;
public:
	static cocos2d::Scene* createScene();
	bool init() override;

	CREATE_FUNC(MainMenu);

};
#endif