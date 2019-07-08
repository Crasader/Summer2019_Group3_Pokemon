#pragma once
#include "MyObject.h"
#include <vector>
#include "NPC.h"

using namespace std;

class salesman : public NPC
{
private:
	string name;
public:
	salesman(Scene* scene);
	~salesman();
	void Init() override;
	void Update(float deltaTime) override;
};
