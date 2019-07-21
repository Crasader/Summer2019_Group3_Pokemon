#pragma once
#include <string>
#include <map>
#include <cocos2d.h>
#include <ui\CocosGUI.h>
using namespace cocos2d;
using namespace ui;
using namespace std;

class ResourceManager
{
private:
	static ResourceManager* m_instance;
	ResourceManager();
	Sprite* DuplicateSprite(Sprite* sprite);
	map<int, TMXTiledMap*> m_tiledmaps;
	map<int, Sprite*> m_sprites;
	map<int, Animation*> m_animations;
	map<int, Button*> m_buttons;
	map<int, Label*> m_labels;
public:
	~ResourceManager();
	static ResourceManager* GetInstance();
	void Init();
	void Load();
	TMXTiledMap* GetTiledMapById(int id);
	Sprite* GetSpriteById(int id);
	Animation* GetAnimationById(int id);
	Button* GetButtonById(int id);
	Label* GetLabelById(int id);
};