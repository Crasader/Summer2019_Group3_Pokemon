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
	virtual void SetPower(int x)=0;
	virtual void SetPP(int y)=0;
	virtual void SetMaxPP(int m) = 0;
	virtual void SetIdType(int it) = 0;
	virtual void SetName(string n)=0;
	virtual void SetType(string st)=0;
	int GetMaxPP();
	int GetPower();
	int GetPP();
	int GetIdType();
	string GetName();
	string GetType();
private:
	int m_power;
	int m_pp;
	string m_name;
	string m_type;
	int m_idtype;
	int m_maxpp;
};
