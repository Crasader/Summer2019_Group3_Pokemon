#pragma once
#include"cocos2d.h"
#include<string>
using namespace std;
using namespace cocos2d;
USING_NS_CC;

class Attack
{
private:
	int m_power;
	int m_pp;
	string m_name;
	string m_type;
	int m_idtype;
	int m_maxpp;
public:
	Attack();
	~Attack();
	void SetPower(int x);
	void SetPP(int y);
	void SetMaxPP(int m);
	void SetIdType(int it);
	void SetName(string n);
	void SetType(string st);
	int GetMaxPP();
	int GetPower();
	int GetPP();
	int GetIdType();
	string GetName();
	string GetType();
};
