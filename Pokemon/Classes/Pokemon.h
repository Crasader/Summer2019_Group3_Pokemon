#pragma once
#include "MyObject.h"
#include <vector>
using namespace std;

class Pokemon : public MyObject
{
protected:
	string m_name;
	int m_type;

	int m_maxHealth;
	int m_currentHealth;
	int m_level;
	int m_attack;
	int m_defense;
	int m_attackSpeed;
	int m_currentExp;
	int m_maxExp;
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
};