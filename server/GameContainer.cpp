/*
 * GameContainer.cpp
 *
 *  Created on: 17.01.2013
 *      Author: Henrik
 */

#include "server/GameContainer.h"

using namespace std;

GameContainer::GameContainer() {
	// TODO Auto-generated constructor stub

}

GameContainer::~GameContainer() {
	// TODO Auto-generated destructor stub
}

void GameContainer::addArmy(EArmyPtr army) {
	armylist.insert(armylist.end(),army);
}

void GameContainer::removeArmy(EArmyPtr army) {
	int counter=0;
	for(auto ar:armylist){
		if(ar==army){
			armylist.erase(armylist.begin()+counter);
		}
		counter++;
	}
}

void GameContainer::addLocation(ELocationPtr location) {
	locationlist.insert(locationlist.end(),location);
}

void GameContainer::removeLocation(ELocationPtr location) {
	int counter=0;
		for(auto loc:locationlist){
			if(loc==location){
				locationlist.erase(locationlist.begin()+counter);
				break;
			}
			counter++;
		}
}

void GameContainer::addPlayer(PlayerPtr player) {
	playerlist.insert(playerlist.end(),player);
}

void GameContainer::removePlayer(PlayerPtr player) {
	int counter=0;
	for(auto p:playerlist){
		if(p==player){
			playerlist.erase(playerlist.begin()+counter);
			break;
		}
		counter++;
	}
}

EArmyPtr GameContainer::getArmyAt(coordinates coords) {
	for(auto army:armylist){
		if(army->getCoords().x==coords.x and army->getCoords().y==coords.y){
			return army;
			break;
		}
	}
}

ELocationPtr GameContainer::getLocationAt(coordinates coords) {
	for(auto loc:locationlist){
		if(loc->getCoords().x==coords.x and loc->getCoords().y==coords.y){
			return loc;
			break;
		}
	}
}

boost::uuids::uuid GameContainer::whosePlaceAt(coordinates coords) {
	for(auto loc:locationlist){
			if(loc->getCoords().x==coords.x and loc->getCoords().y==coords.y){
				return loc->GetOwner();
				break;
			}
		}
}

boost::uuids::uuid GameContainer::whoseArmyAt(coordinates coords) {
	for(auto army:armylist){
			if(army->getCoords().x==coords.x and army->getCoords().y==coords.y){
				return army->GetOwner();
				break;
			}
		}
}

PlayerPtr GameContainer::getPlayerById(boost::uuids::uuid playerId) {
	for(PlayerPtr player:playerlist){
		if(player->getPlayerId()==playerId){
			return player;
			break;
		}
	}
}

int GameContainer::getPlayerCount(){
	return playerlist.size();
}

vector<EArmyPtr>* GameContainer::getArmyListPtr() {
	return &armylist;
}

vector<ELocationPtr>* GameContainer::getLocationListPtr() {
	return &locationlist;
}

void GameContainer::addUnit(EUnitPtr unit) {
	unitlist.insert(unitlist.end(),unit);
}

void GameContainer::removeUnit(EUnitPtr unit) {
	int counter=0;
	for(auto u:unitlist){
		if(u==unit){
			unitlist.erase(unitlist.begin()+counter);
			break;
		}
		counter++;
	}
}

vector<EUnitPtr>* GameContainer::getUnitVectorPtrByArmy(EArmyPtr army) {
	return &(army->units);
}

vector<PlayerPtr>* GameContainer::getPlayerListPtr() {
	return &playerlist;
}

EArmyPtr GameContainer::getArmy(int index) {
	return armylist[index];
}

EUnitPtr GameContainer::getUnit(int index) {
	return unitlist[index];
}

ELocationPtr GameContainer::getLocation(int index) {
	return locationlist[index];
}

PlayerPtr GameContainer::getPlayer(int index) {
	return playerlist[index];
}

vector<EUnitPtr>* GameContainer::getUnitListPtr() {
	return &unitlist;
}
