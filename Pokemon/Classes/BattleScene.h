#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
using namespace cocos2d;

class BattleScene : public Layer
{
private:
	Button* m_buttonFight;
	Button* m_buttonBag;
	Button* m_buttonPokemon;
	Button* m_buttonRun;
	Label* m_labelSkill1;
	Label* m_labelSkill2;
	Label* m_labelSkill3;
	Label* m_labelSkill4;
	Label* m_labelOppHealth;
	Label* m_labelBattleLog;
	TMXTiledMap* m_tiledmap;
	Pokemon* player;
	Pokemon* opponent;
	int writing = 0;
	bool m_state = false;
public:
	BattleScene();
	~BattleScene();
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float deltaTime) override;
	void type(float deltaTime);

	void InitTiledMap();

	void InitButton();

	void InitObject();

	void AddEventListener();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* e);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* e);

	bool onTouchBegan(Touch* touch, Event* e);

	void BattleLog(string logg);

	void SetVisible(bool visible);

	void DamagePhase(int idSkill);

	CREATE_FUNC(BattleScene);
};