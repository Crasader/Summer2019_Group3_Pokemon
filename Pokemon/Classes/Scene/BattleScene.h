#pragma once
#include "cocos2d.h"
#include "Pokemon.h"
#include "include_pokemon.h"
using namespace cocos2d;

class BattleScene : public Layer
{
private:
	Sprite* m_pokeball;
	Animation* m_animationPokeball;

	Sprite* m_background;
	Sprite* m_messageBox;
	Button* m_buttonFight;
	Button* m_buttonBag;
	Button* m_buttonPokemon;
	Button* m_buttonRun;
	Label* m_labelSkill1;
	Label* m_labelSkill2;
	Label* m_labelSkill3;
	Label* m_labelSkill4;
	Label* m_labelBattleLog;

	Label* m_labelOppLevel;
	Label* m_labelOppName;
	Sprite* m_hpPlayer;

	Label* m_labelPlayerLevel;
	Label* m_labelPlayerName;
	Sprite* m_hpOpponent;

	TMXTiledMap* m_tiledmap;

	Pokemon* m_player;
	Skill* m_playerSkill;
	Pokemon* m_opponent;
	Skill* m_oppSkill;
	int writing = 0;
	bool m_stateBattleMessage = false;
	bool m_statePlayer = false;
	bool m_stateOpponent = false;
public:
	BattleScene();
	~BattleScene();
	static cocos2d::Scene* createScene();

	virtual bool init();

	void update(float deltaTime) override;

	void ReleaseChildren();

	void TypeWriter(float deltaTime);

	void ResetAllState();

	Pokemon* GetTrainerPokemon();

	void PlayerAttackOpponent();

	void OpponentAttackPlayer();

	void DamageStepWithPlayerAttackFirst(float deltaTime);

	void DamageStepWithOpponentAttackFirst(float deltaTime);

	void ChangePokemonStep(float deltaTime);

	void ReduceHpPlayer(float deltaTime);

	void ReduceHpOpponent(float deltaTime);

	void BattleMessageSetOpacity(GLubyte opacity);

	void LoadPlayerPosition();

	void LoadPlayerHpBar();

	void InitTiledMap();

	void InitUI();

	void InitObject();

	void AddEventListener();

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* e);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* e);

	bool onTouchBegan(Touch* touch, Event* e);

	void BattleMessage(string logg);

	void SetButtonVisible(bool visible);

	void StartBattle();

	void HasNextBattle();

	void BattlePhase(int idSkill);

	void TrainerChangePokemon();

	void StandByPhase();

	void EndBattle();

	CREATE_FUNC(BattleScene);
};