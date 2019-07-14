#pragma once
#include "MyObject.h"
#include "Skill.h"
#include "Skill\Tackle.h"
#include "Skill\Bite.h"
#include <vector>
using namespace std;

class Pokemon : public MyObject
{
private:
	float RandomFloat(float a, float b);
protected:
	string m_name;
	vector<Skill*> m_skills = { new Tackle(),new Bite(),nullptr };
	int m_type;
	int m_maxHealth;
	int m_currentHealth;
	int m_level;
	int m_attack;
	int m_defense;
	int m_attackSpeed;
	int m_currentExp;
	int m_maxExp;
	bool m_alive = true;
	bool m_state = false;
public:
	Pokemon();
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
	Skill* GetSkillById(int id);
	int GetCountSkills();
	void Attack(Pokemon* target, Skill* skill);
};