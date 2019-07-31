#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "Trainer.h"
#include <math.h>
using namespace cocos2d;
using namespace std;
class Town : public cocos2d::Layer
{
private:
	Trainer * mPlayer;
	Sprite * mGateWay;
	TMXTiledMap* map;
public:
	static int arrayGrassHasPokemon[32][16];
	static cocos2d::Scene* createScene();
	int Check(int x, int y);
	static int previousScene;
	virtual bool init();
	bool onContactBegin(PhysicsContact & contact);
	void InitObject();
	void UpdateCamera();
	static void InitArray();
	CREATE_FUNC(Town);
	void UpdatePlayer(float dt);
	void update(float);
	void DeleteGrassHasPokemon();
};