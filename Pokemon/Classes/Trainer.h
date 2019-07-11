#include "Bag.h"
#include "MyObject.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace cocos2d;
class Trainer : public MyObject
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
	Sprite* GetSprite();
private:

	Sprite* m_sprite;
	Bag* bag;

};

