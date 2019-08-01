#pragma once
#include "MyObject.h"
#include "Skill.h"
#include "include_skill.h"
#include <vector>
using namespace std;

class Pokemon : public MyObject
{
private:
	float RandomFloatNumber(float a, float b);
protected:
	string m_name;
	Animation* animationFront;
	Animation* animationBack;
	vector<Skill*> m_listSkill = { nullptr, nullptr, nullptr };
	int m_type;
	int m_maxHealth = 0;
	int m_currentHealth = 0;
	int m_level = 1;
	int m_attack = 0;
	int m_defense = 0;
	int m_attackSpeed = 0;
	int m_currentExp = 0;
	int m_maxExp = 0;
	bool m_alive = true;
	bool m_state = false;
	bool m_evolved = false;
public:
	Pokemon();
	Pokemon(int level);
	~Pokemon();
	void Init() override;
	void Init(int id_front, int id_back) override;
	void Update(float deltaTime) override;

	virtual Pokemon* Evolve();

	void LevelUp();
	string GetName();
	void SetName(string name);
	int GetType();
	void SetType(int type);
	int GetMaxHP();
	void SetMaxHP(int health);
	int GetCurrentHP();
	void SetCurrentHP(int health);
	int GetLevel();
	void SetLevel(int level);
	int GetAtk();
	void SetAtk(int atk);
	int GetDef();
	void SetDef(int def);
	int GetAtkSpeed();
	void SetAtkSpeed(int atkSpeed);
	int GetCurrentExp();
	void SetCurrentExp(int exp);
	int GetMaxExp();
	void SetMaxExp(int exp);
	bool IsAlive();
	void SetState(bool state);
	bool GetState();
	void SetPosition(float xx, float yy);
	void SetPosition(Vec2 position);
	void SetScale(float scale);
	void RemoveFromParent();
	Vec2 GetPosition();
	void LearnSkill(Skill* skill);
	Skill* GetSkillById(int id);
	int GetCountSkills();
	void Attack(Pokemon* target, Skill* skill);
	void Restore();
};