#pragma once
#include"cocos2d.h"
#include "Attack.h"

class Tackle : public Attack	 
{
public:
	Tackle();
	~Tackle();
	string GetName();
	string GetType();
	void Init();
	void SetName(string n);
	void SetType(string t);
private:
	string name;
	string type;
	
};
