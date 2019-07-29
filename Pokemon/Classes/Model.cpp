#include "Model.h"

Model::Model() {

}

Model::~Model() {

}

int Model::stateGame = 0;

string Model::GetTipsGame()
{
	if (stateGame == 0) {
		return "You must go to the Doctoc's House to get pokemon! If you have not Pokemon, you couldn't battle with NPC";
	}
	else if (stateGame == 1) {
		return "You can go to the grass to get pokemon or battle with npc!";
	}
	else
		return "tai oc cho qua di";
}
void Model::SetStateGame(int state) {
	if (state > stateGame) {
		stateGame = state;
	}
	else return;
}