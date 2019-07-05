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
	/*length = document["BUTTON"]["length"].GetInt();
	for (int i = 0; i < length; i++)
	{
		string key = to_string(i);
		string path = document["BUTTON"][key.c_str()]["normal"].GetString();
		path.replace(0, 2, this->m_dataFolderPath);
		string path1 = document["BUTTON"][key.c_str()]["pressed"].GetString();
		path1.replace(0, 2, this->m_dataFolderPath);
		auto button = Button::create(path, path1);
		button->retain();
		this->m_buttons.insert(pair<int, Button*>(i, button));
	}
	length = document["FONT"]["length"].GetInt();
	for (int i = 0; i < length; i++)
	{
		string key = to_string(i);
		string path = document["FONT"][key.c_str()].GetString();
		path.replace(0, 2, this->m_dataFolderPath);
		auto label = Label::createWithTTF("", path, 15);
		label->retain();
		this->m_labels.insert(pair<int, Label*>(i, label));
	}*/
	length = document["ANIMATE"]["size"].GetInt();
	for (int i = 0; i < length; i++)
	{
		string key = to_string(i);
		string plist_path = document["ANIMATE"][key.c_str()]["plist"].GetString();
		string path = document["ANIMATE"][key.c_str()]["path"].GetString();
		int n = document["ANIMATE"][key.c_str()]["size"].GetInt();
		SpriteFrameCache::getInstance()->destroyInstance();
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plist_path, path);
		Vector<SpriteFrame*> aniFrames;
		for (int j = 0; j < n; j++)
		{
			string frameName = document["ANIMATE"][key.c_str()]["png"][j].GetString();
			aniFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
		}
		auto animation = Animation::createWithSpriteFrames(aniFrames, 0.2);
		auto animate = Animate::create(animation);
		animate->retain();
		this->m_animates.insert(pair<int, Animate*>(i, animate));
	}
}

Sprite * ResourceManager::GetSpriteById(int id)
{
	auto tmp = this->m_sprites.find(id);
	while (tmp != m_sprites.end())
	{
		return tmp->second;
	}
	
}

Animate * ResourceManager::GetAnimateById(int id)
{
	auto tmp = this->m_animates.find(id);
	while (tmp != m_animates.end())
	{
		return tmp->second;
	}
}

Button * ResourceManager::GetButtonById(int id)
{
	auto tmp = this->m_buttons.find(id);
	while (tmp != m_buttons.end())
	{
		return tmp->second;
	}
}

Label * ResourceManager::GetLabelById(int id)
{
	auto tmp = this->m_labels.find(id);
	while (tmp != m_labels.end())
	{
		return tmp->second;
	}
}
