
#include"cocos2d.h"
USING_NS_CC;
using namespace cocos2d;
class Trainer 
{
public: 
	Trainer();
	Trainer(cocos2d::Layer* layer);
	~Trainer();
	void Init(cocos2d::Layer* layer);
	void walkLeft();
	void walkRight();
	void walkUp();
	void walkDown();
	void setPosition(cocos2d::Vec2 pos);
	cocos2d::Vec2 getPosition();
	Sprite* GetSprite();
private:
	Sprite* m_sprite;
};

