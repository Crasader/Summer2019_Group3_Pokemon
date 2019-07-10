#pragma once
#include"cocos2d.h"
#include"Model.h"
USING_NS_CC;
class Trainer : public Model
{
public: 
	Trainer(cocos2d::Layer* layer);
	~Trainer();

	static const int walk_speed = 5;
	static const int run_speed = 10;

	static const int anime_idleUp = 0;
	static const int anime_walkUp = anime_idleUp + 1;
	static const int anime_runUp = anime_walkUp + 1;

	static const int anime_idleDown = anime_runUp + 1;
	static const int anime_walkDown = anime_idleDown + 1;
	static const int anime_runDown = anime_walkDown + 1;

	static const int anime_idleLeft = anime_runDown + 1;
	static const int anime_walkLeft = anime_idleLeft + 1;
	static const int anime_runLeft = anime_walkLeft + 1;

	static const int anime_idleRight = anime_runLeft + 1;
	static const int anime_walkRight = anime_idleRight + 1;
	static const int anime_runRight = anime_walkRight + 1;

	static const int anime_total = anime_runRight + 1;

	static const int state_start = 0;

	static const int state_idleUp = state_start + 1;
	static const int state_walkUp = state_idleUp + 1;
	static const int state_runUp = state_walkUp + 1;

	static const int state_idleDown = state_runUp + 1;
	static const int state_walkDown = state_idleDown + 1;
	static const int state_runDown = state_walkDown + 1;

	static const int state_idleLeft = state_runDown + 1;
	static const int state_walkLeft = state_idleLeft + 1;
	static const int state_runLeft = state_walkLeft + 1;

	static const int state_idleRight = state_runLeft + 1;
	static const int state_walkRight = state_idleRight + 1;
	static const int state_runRight = state_walkRight + 1;

	void setState(int nextState);
	int getCurrentState();
	void walkLeft();
	void walkRight();
	void walkUp();
	void walkDown();
	void runLeft();
	void runRight();
	void runUp();
	void runDown();
	void update(float);
	Sprite * GetSprite();
private:
	int m_currentState;
	cocos2d::Action* m_animation[anime_total];
};

