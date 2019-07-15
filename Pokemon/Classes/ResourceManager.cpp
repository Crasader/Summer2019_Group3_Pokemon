#include "ResourceManager.h"
#include "json\rapidjson.h"
#include "json\document.h"
using namespace rapidjson;

ResourceManager::ResourceManager()
{
	this->Init();
}


ResourceManager::~ResourceManager()
{
}

ResourceManager* ResourceManager::s_instance = nullptr;

ResourceManager * ResourceManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new ResourceManager();
	}
	return s_instance;
}

void ResourceManager::Init()
{
	this->Load();
}

void ResourceManager::Load()
{
	auto data = FileUtils::getInstance()->getStringFromFile("res/Data.json");
	Document document;
	document.Parse(data.c_str());
	int length = document["SPRITE"]["size"].GetInt();
	for (int i = 0; i < length; i++)
	{
		string key = to_string(i);
		string path = document["SPRITE"][key.c_str()].GetString();
		auto sprite = Sprite::create(path);
		sprite->retain();
		this->m_sprites.insert(pair<int, Sprite*>(i, sprite));
	}
	length = document["BUTTON"]["size"].GetInt();
	for (int i = 0; i < length; i++)
	{
		string key = to_string(i);
		string path = document["BUTTON"][key.c_str()]["normal"].GetString();
		string path1 = document["BUTTON"][key.c_str()]["pressed"].GetString();
		auto button = Button::create(path, path1);
		button->retain();
		this->m_buttons.insert(pair<int, Button*>(i, button));
	}
	length = document["FONT"]["size"].GetInt();
	for (int i = 0; i < length; i++)
	{
		string key = to_string(i);
		string path = document["FONT"][key.c_str()].GetString();
		auto label = Label::createWithTTF("", path, 15);
		label->retain();
		this->m_labels.insert(pair<int, Label*>(i, label));
	}
	length = document["ANIMATION"]["size"].GetInt();
	for (int i = 0; i < length; i++)
	{
		string key = to_string(i);
		string plist_path = document["ANIMATION"][key.c_str()]["plist"].GetString();
		string path = document["ANIMATION"][key.c_str()]["path"].GetString();
		int n = document["ANIMATION"][key.c_str()]["size"].GetInt();
		SpriteFrameCache::getInstance()->destroyInstance();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_path, path);
		Vector<SpriteFrame*> aniFrames;
		for (int j = 0; j < n; j++)
		{
			string frameName = document["ANIMATION"][key.c_str()]["png"][j].GetString();
			aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		auto animation = Animation::createWithSpriteFrames(aniFrames);
		animation->retain();
		this->m_animations.insert(pair<int, Animation*>(i, animation));
	}
	length = document["TILEDMAP"]["size"].GetInt();
	for (int i = 0; i < length; i++)
	{
		string key = to_string(i);
		string path = document["TILEDMAP"][key.c_str()].GetString();
		auto tiledmap = TMXTiledMap::create(path);
		tiledmap->retain();
		this->m_tiledmaps.insert(pair<int, TMXTiledMap*>(i, tiledmap));
	}
}

TMXTiledMap * ResourceManager::GetTiledMapById(int id)
{
	auto tmp = this->m_tiledmaps.find(id);
	while (tmp != m_tiledmaps.end())
	{
		return tmp->second;
	}
}

Sprite * ResourceManager::DuplicateSprite(Sprite * sprite)
{
	auto temp = Sprite::createWithTexture(sprite->getTexture());
	temp->retain();
	return temp;
}

Sprite * ResourceManager::GetSpriteById(int id)
{
	auto tmp = this->m_sprites.find(id);
	while (tmp != m_sprites.end())
	{
		return this->DuplicateSprite(tmp->second);
	}
}

Animation * ResourceManager::GetAnimationById(int id)
{
	auto tmp = this->m_animations.find(id);
	while (tmp != m_animations.end())
	{
		auto animation = tmp->second->clone();
		animation->retain();
		return animation;
	}
}

Button * ResourceManager::GetButtonById(int id)
{
	auto tmp = this->m_buttons.find(id);
	while (tmp != m_buttons.end())
	{
		auto button = (Button*)tmp->second->clone();
		button->retain();
		return button;
	}
}

Label * ResourceManager::GetLabelById(int id)
{
	auto tmp = this->m_labels.find(id);
	while (tmp != m_labels.end())
	{
		auto label = Label::createWithTTF(tmp->second->getTTFConfig(), "");
		label->retain();
		return label;
	}
}