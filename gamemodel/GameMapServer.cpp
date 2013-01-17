/*
 * GameMapServer.cpp
 *
 *  Created on: 17.01.2013
 *      Author: Henrik
 */

#include "gamemodel/GameMapServer.h"

GameMapServer::GameMapServer() {
	// TODO Auto-generated constructor stub

}

GameMapServer::GameMapServer(GameContainer *container){

}

GameMapServer::~GameMapServer() {
	// TODO Auto-generated destructor stub
}

void GameMapServer::createPlaces() {
}

void GameMapServer::createArmyAt(coordinates coords, PlayerPtr player) {
}

ELocationPtr GameMapServer::getPlaceAt(coordinates coords) {
}

boost::uuids::uuid GameMapServer::whoseLocationAt(coordinates coords) {
	if(this->isPlace(coords) or this->isStartBase(coords)){
		for(auto location:*(container->locationlist)){
			if(location->getCoords().x==coords.x and location->getCoords().y==coords.y){
				return location->GetOwner();
			}
		}
	}
}

EArmyPtr GameMapServer::getArmyAt(coordinates coords) {
	if(this->isArmyPositioned(coords)){
		for(auto army:*(container->getArmyListPtr())){
			if(army->getCoords().x==coords.x and army->getCoords().y==coords.y){
				return army;
			}
		}
	}
}

boost::uuids::uuid GameMapServer::whoseArmyAt(coordinates coords) {

}
