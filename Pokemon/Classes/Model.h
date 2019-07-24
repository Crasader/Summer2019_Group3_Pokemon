#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class Model
{
protected:
	
public:
	Model();
	~Model();

	static const int BITMASK_WORLD = 100;
	static const int BITMASK_PLAYER = BITMASK_WORLD + 1;

	static const int MODLE_TYPE_MAIN_CHARACTER = 1;
	
	//Home
	static const int MODLE_TYPE_HOUSE_GATE = 2;
	static const int BITMASK_HOUSE_GATE = BITMASK_PLAYER + 1;

	//HomeTown
	static const int MODLE_TYPE_TOWN_GATE_TO_HOUSE = 2;
	static const int MODLE_TYPE_TOWN_GATE_TO_ROUTE1 = 4; 
	static const int MODLE_TYPE_TOWN_GATE_TO_LAB = 3;

	static const int PRESCENE_HOUSE_TO_TOWN = 0;
	static const int PRESCENE_LAB_TO_TOWN = 1;
	static const int PRESCENE_ROUTE1_TO_TOWN = 2;

	static const int BITMASK_TOWN_GATE_TO_HOUSE = BITMASK_PLAYER + 1;
	static const int BITMASK_TOWN_GATE_TO_ROUTE1 = BITMASK_TOWN_GATE_TO_HOUSE +1;
	static const int BITMASK_TOWN_GATE_TO_LAB = BITMASK_TOWN_GATE_TO_ROUTE1 + 1;
	//Route1

	static const int BITMASK_ROUTE1_GATE_TO_TOWN = BITMASK_TOWN_GATE_TO_LAB +1;
	static const int BITMASK_ROUTE1_GATE_TO_CITY = BITMASK_ROUTE1_GATE_TO_TOWN +1;

	static const int MODLE_TYPE_ROUTE1_GATE_TO_TOWN = 2;
	static const int MODLE_TYPE_ROUTE1_GATE_TO_CITY = 3;

	static const int PRESCENE_TOWN_TO_ROUTE1 = 0;
	static const int PRESCENE_CITY_TO_ROUTE1 = 1;

	//LAB
	static const int MODLE_TYPE_DOCTOR = 3;
	static const int MODLE_TYPE_GATEWAY_LAB = 2;

	static const int BITMASK_DOCTOR = BITMASK_ROUTE1_GATE_TO_CITY + 1;
	static const int BITMASK_GATEWAY_TO_TOWN = BITMASK_DOCTOR + 1;

	//pokemoncenter
	static const int BITMASK_GATEWAY_TO_CITY = BITMASK_DOCTOR + 1;
	static const int MODLE_TYPE_GATEWAY_PC = 2;

	static const int BITMASK_POKEMON = BITMASK_GATEWAY_TO_CITY + 1;
	static const int STATE_GAME = 0;
};