#pragma once
#include "cocos2d.h"
#include <ui\CocosGUI.h>
using namespace cocos2d;
using namespace ui;
using namespace std;

class Buttons
{
private:
	Buttons();
	static Buttons *m_button;
	Button *m_up;
	Button *m_right;
	Button *m_left;
	Button *m_down;

public:
	~Buttons();
	static Buttons* getIntance();
	Button *GetButtonUp();
	Button *GetButtonLeft();
	Button *GetButtonRight();
	Button *GetButtonDown();
};

