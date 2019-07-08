#pragma once
#include "MyObject.h"
#include <vector>
#include "NPC.h"

using namespace std;

class Joy : public NPC
{
private:
	string name;
public:
	Joy(Scene* scene);
	~Joy();
	void Init() override;
	void Update(float deltaTime) override;
};
#pragma once
