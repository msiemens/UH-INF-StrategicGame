#include "client/GameClient.h"

#include <sstream>
#include <iostream>
#include <list>

using namespace std;


void GameClient::OnNextTurn(){
	//reset armies m_steps_left_in_round

	for(auto army: player.armies){
		army->SetStepsLeft(2);
	}
	for(auto army: opponent.armies){
		army->SetStepsLeft(2);
	}
	player.SetActionLeft(10);

	// check buildings
}

char* GameClient::getCharArrayByString(string text){
	char * buffer = new char[text.length()];
	strcpy(buffer, text.c_str());
	return buffer;
}

char* GameClient::getCharArrayByInt(int value){
	stringstream temp;
	temp << value;
	char * buffer = new char[temp.str().length()];
	strcpy(buffer, temp.str().c_str());
	return buffer;
}

coordinates GameClient::getCoordsByClick(int mX, int mY){
	int i = 1;
	int x=0;
	int y=0;
	mX += camposx;
	mY += camposy;

	for(i=1; i < map.mapSizeX; i++){
		if(mX > TILE_SIZE){
			mX = mX-TILE_SIZE;
			x++;
		}else{
			break;
		}
	}

	for(i=1; i < map.mapSizeY; i++){
		if(mY > TILE_SIZE){
			mY = mY-TILE_SIZE;
			y++;
		}else{
			break;
		}
	}
	coordinates coords(x,y);
	return coords;
}

EArmyPtr GameClient::getArmyByCoords(coordinates coords){
	EArmyPtr armyat;
	for (auto army: player.armies) {
		if (army->getCoords().x == coords.x and  army->getCoords().y == coords.y) {
			armyat = army;
			break;
		}
	}
	return armyat;
}

EArmyPtr GameClient::getOpponentArmyByCoords(coordinates coords){
	EArmyPtr armyat;
	for (auto army: opponent.armies) {
		if (army->getCoords().x == coords.x and  army->getCoords().y == coords.y) {
			armyat = army;
			break;
		}
	}
	return armyat;
}
