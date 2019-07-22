#pragma once
#include "cocos2d.h"
#include "MyObject.h"
#include <string>
using namespace std;
using namespace cocos2d;
USING_NS_CC;

class Skill : public MyObject
{
protected:
	int m_power;
	int m_pp;
	string m_name;
	string m_type;
	int m_idtype;
	int m_maxpp;
	Animation* m_animation;
	bool m_state = false;
public:
	Skill();
	~Skill();
	virtual void Init() override {};
	virtual void Update(float deltaTime) override {};
	void SetPower(int x);
	void SetCurrentPP(int y);
	void SetMaxPP(int m);
	void SetIdType(int it);
	void SetName(string n);
	void SetTypeName(string st);
	int GetMaxPP();
	int GetPower();
	int GetPP();
	int GetIdType();
	string GetName();
	string GetType();
	void SetState(bool state);
	bool GetState();
	void SetPosition(float xx, float yy);
	void SetPosition(Vec2 position);
	Vec2 GetPosition();
	void SetAnimation(int id);
	Animation* GetAnimation();
	virtual void Run(Vec2 position);
	void SetScale(float scale);
};