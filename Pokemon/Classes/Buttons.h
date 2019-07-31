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
	Button *m_bag;
	Button *m_tips;
public:
	~Buttons();
	static int state;
	static Buttons* GetIntance();
	int IsContainUp(Vec2 t, Trainer *mPlayer);
	void ButtonListener(Trainer *&mPlayer);
	float Cos(Vec2 a, Vec2 b);
	//void ButtonBagListener(Layer * layer, Camera* camera);
	//void ButtonTipListener(Layer * layer, Camera * camera);
	Button *GetButtonUp();
	Button *GetButtonBag();
	Button *GetButtonTips();
	void SetVisible(bool enable);
	void Remove();
	void UpdateButton(float x, float y);
	void SetTouchEnable();
	void SetTouchDisable();
};