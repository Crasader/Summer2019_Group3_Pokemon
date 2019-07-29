#pragma once
#include "cocos2d.h"
#include <string>
using namespace std;
using namespace cocos2d;

class Model
{
protected:
	
public:
	Model();
	~Model();

	static string GetTipsGame();

	static void SetStateGame(int state);

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

	static const int BITMASK_TOWN_GATE_TO_HOUSE = BITMASK_HOUSE_GATE + 1;
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
	static const int BITMASK_GATEWAY_TO_CITY = BITMASK_GATEWAY_TO_TOWN + 1;
	static const int MODLE_TYPE_GATEWAY_PC = 2;

	static const int BITMASK_POKEMON = BITMASK_GATEWAY_TO_CITY + 1;
	static int stateGame;
	// City
	static const int BITMASK_CITY_GATE_TO_ROUTE1 = BITMASK_POKEMON + 1;
	static const int BITMASK_CITY_GATE_TO_PC = BITMASK_CITY_GATE_TO_ROUTE1 + 1;
	static const int BITMASK_CITY_GATE_TO_CAVE = BITMASK_CITY_GATE_TO_PC + 1;
	static const int BITMASK_CITY_GATE_TO_LAKE = BITMASK_CITY_GATE_TO_CAVE + 1;
	static const int BITMASK_CITY_GATE_TO_ROUTE2 = BITMASK_CITY_GATE_TO_LAKE + 1;

	static const int MODLE_TYPE_CITY_GATE_TO_ROUTE1 = 2;
	static const int MODLE_TYPE_CITY_GATE_TO_PC = 3;
	static const int MODLE_TYPE_CITY_GATE_TO_CAVE = 4;
	static const int MODLE_TYPE_CITY_GATE_TO_LAKE = 5;
	static const int MODLE_TYPE_CITY_GATE_TO_ROUTE2 = 6;

	static const int PRESCENE_ROUTE1_TO_CITY = 0;
	static const int PRESCENE_PC_TO_CITY = 1;
	static const int PRESCENE_CAVE_TO_CITY = 2;
	static const int PRESCENE_LAKE_TO_CITY = 3;
	static const int PRESCENE_ROUTE2_TO_CITY = 4;

	//CAVE
	static const int MODLE_TYPE_CAVE_GATE = 2;
	static const int BITMASK_CAVE_GATE = BITMASK_PLAYER + 1;

	//LAKE
	static const int MODLE_TYPE_LAKE_GATE = 2;
	static const int BITMASK_LAKE_GATE = BITMASK_PLAYER + 1;

	//Route2
	static const int BITMASK_ROUTE2_GATE_TO_CITY = BITMASK_CITY_GATE_TO_ROUTE2 + 1;
	static const int BITMASK_ROUTE2_GATE_TO_ROAD = BITMASK_ROUTE2_GATE_TO_CITY + 1;

	static const int MODLE_TYPE_ROUTE2_GATE_TO_CITY = 2;
	static const int MODLE_TYPE_ROUTE2_GATE_TO_ROAD = 3;

	static const int PRESCENE_CITY_TO_ROUTE2 = 0;
	static const int PRESCENE_ROAD_TO_ROUTE2 = 1;

	//ROAD
	static const int BITMASK_ROAD_GATE_TO_ROUTE2 = BITMASK_ROUTE2_GATE_TO_ROAD + 1;
	static const int BITMASK_ROAD_GATE_TO_LEAGUE = BITMASK_ROAD_GATE_TO_ROUTE2 + 1;

	static const int MODLE_TYPE_ROAD_GATE_TO_ROUTE2 = 2;
	static const int MODLE_TYPE_ROAD_GATE_TO_LEAGUE = 3;

};