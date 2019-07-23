#pragma once
#include "cocos2d.h"
#include "Trainer.h"
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
	static int state;
	static Buttons* GetIntance();
	void ButtonListener(Trainer *&mPlayer);
	Button *GetButtonUp();
	Button *GetButtonLeft();
	Button *GetButtonRight();
	Button *GetButtonDown();
	void Remove();
	void UpdateButton(float x, float y);
};