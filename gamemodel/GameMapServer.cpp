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
		for(int i=0;i<container->getLocationCount();i++){
			if(container->getLocation(i)->getCoords().x==coords.x and
					container->getLocation(i)->getCoords().y==coords.y){
				return container->getLocation(i);
			}
		}
	}
}

EArmyPtr GameMapServer::getArmyAt(coordinates coords) {
	if(this->isArmyPositioned(coords)){
		for(int i=0;i<container->getArmyCount();i++){
			if(container->getArmy(i)->getCoords().x==coords.x and
					container->getArmy(i)->getCoords().y==coords.y){
				return container->getLocation(i);
			}
		}
	}
}

boost::uuids::uuid GameMapServer::whoseArmyAt(coordinates coords) {
}
