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
	static ResourceManager* s_instance;
	ResourceManager();
	Sprite* DuplicateSprite(Sprite* sprite);
	map<int, TMXTiledMap*> m_tiledmaps;
	map<int, Sprite*> m_sprites;
	map<int, Animate*> m_animates;
	map<int, Button*> m_buttons;
	map<int, Label*> m_labels;
public:
	~ResourceManager();
	static ResourceManager* GetInstance();
	void Init();
	void Load();
	TMXTiledMap* GetTiledMapById(int id);
	Sprite* GetSpriteById(int id);
	Animate* GetAnimateById(int id);
	Button* GetButtonById(int id);
	Label* GetLabelById(int id);
};