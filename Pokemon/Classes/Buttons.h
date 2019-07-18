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
	Button *m_bag;

public:
	~Buttons();
	static Buttons* getIntance();
	void ButtonListener(Trainer *&mPlayer);
	void ButtonBag(Layer * layer, Vec2 vec);
	//void ButtonBag(Layer* layer);
	Button *GetButtonUp();
	Button *GetButtonLeft();
	Button *GetButtonRight();
	Button *GetButtonDown();
	Button *GetButtonBag();
	void UpdateButton(float x, float y);
};

