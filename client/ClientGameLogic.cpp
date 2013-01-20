#include "client/GameClient.h"


#include <iostream>
#include <list>

using namespace std;


void GameClient::OnNextTurn(){
	//reset armies m_steps_left_in_round

	for(auto army: player.armies){
		army->SetStepsLeft(3);
	}
	for(auto army: opponent.armies){
		army->SetStepsLeft(3);
	}

	// check buildings
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


void GameClient::MergeArmyIntoPlace(coordinates coords, EArmyPtr Army){
	int i=0;
	ELocationPtr place = map.getPlaceAt(coords);
	if(10 - place->town_army->units.size() > Army->units.size()){
		for(i=0; i<Army->units.size(); i++){
			place->town_army->units.push_back(Army->units[i]);
		}
		Army->units.clear();
		map.setWalkable(ArmySelected->getCoords());
		ArmySelected.reset();
		player.armies.remove(Army);
	}
}

void GameClient::MergeArmies(coordinates coords, EArmyPtr Army){
	int i=0;
	EArmyPtr armyat = getArmyByCoords(coords);
	if(armyat->units.size() + Army->units.size() <= 10){
		for(i=0; i<Army->units.size(); i++){
			armyat->units.push_back(Army->units[i]);
		}
		Army->units.clear();
		map.setWalkable(ArmySelected->getCoords());
		ArmySelected=armyat;
		player.armies.remove(Army);
	}
}

