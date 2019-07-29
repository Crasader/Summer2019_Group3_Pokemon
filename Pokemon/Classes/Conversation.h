#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string>
using namespace cocos2d;
using namespace std;
class Converstation
{
public:
	void Init(cocos2d::Layer * layer);
	Converstation(cocos2d::Layer * layer);
	~Converstation();
	void LogSetOpacity(GLubyte opacity);
	void Log(string logg);
	void TypeWriter(float deltaTime);
private:
	Sprite* m_messageBox;
	Label* m_labelLog;
	int writing = 0;
	Layer *scene;
};
