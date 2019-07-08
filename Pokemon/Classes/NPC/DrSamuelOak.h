#pragma once
#include "MyObject.h"
#include <vector>
#include "NPC.h"

using namespace std;

class DrSamuelOak : public NPC
{
private:
	string name;
public:
	DrSamuelOak(Scene* scene);
	~DrSamuelOak();
	void Init() override;
	void Update(float deltaTime) override;
};
