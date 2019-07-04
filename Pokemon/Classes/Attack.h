#pragma once
#include"cocos2d.h"
#include<string>
using namespace std;
using namespace cocos2d;
USING_NS_CC;

class Attack
{
public:
	Attack();
	~Attack();
	virtual int GetPower()=0;
	virtual int GetPP()=0;
	virtual void SetPower(int x)=0;
	virtual void SetPP(int y)=0;
	Animate* getAnimate(int id);
private:
	int m_power;
	int m_pp;
	Animate* m_animate;
};
