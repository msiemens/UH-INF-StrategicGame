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

GameMapServer::GameMapServer(GameContainer *container):container(container){
	createPlaces();
}

GameMapServer::~GameMapServer() {
	// TODO Auto-generated destructor stub
}

void GameMapServer::createPlaces() {
	for(int y=0;y<this->mapSizeY;y++){
		for(int x=0;x<this->mapSizeX;x++){
			if(this->isPlace(coordinates(x,y)) or this->isStartBase(coordinates(x,y))){
				ELocationPtr location(new ELocation);
				location->setCoords(coordinates(x,y));
				location->SetAssemblyPointCoord(x+1,y);
				container->addLocation(location);
			}
		}
	}
}

void GameMapServer::createArmyAt(coordinates coords, PlayerPtr player) {
	EArmyPtr army(new EArmy);
	army->setCoords(coords);
	army->SetOwner(player->getPlayerId());
	container->addArmy(army);
}

ELocationPtr GameMapServer::getLocationAt(coordinates coords) {
	ELocationPtr loc(new ELocation);
	if(this->isPlace(coords) or this->isStartBase(coords)){
			for(int i=0;i<container->getLocationCount();i++){
				ELocationPtr location(container->getLocation(i));
				if(location->getCoords().x==coords.x and location->getCoords().y==coords.y){
					return location;
				}
			}
		}
	return loc;
}

boost::uuids::uuid GameMapServer::whoseLocationAt(coordinates coords) {
	boost::uuids::uuid id;
	if(this->isPlace(coords)){
		return getLocationAt(coords)->GetOwner();
	}
	return id;
}

EArmyPtr GameMapServer::getArmyAt(coordinates coords) {
	EArmyPtr a(new EArmy);
	if(this->isArmyPositioned(coords)){
		for(auto army:*(container->getArmyListPtr())){
			if(army->getCoords().x==coords.x and army->getCoords().y==coords.y){
				return army;
			}
		}
	}
	return a;
}

boost::uuids::uuid GameMapServer::whoseArmyAt(coordinates coords) {
	boost::uuids::uuid id;
	if(this->isArmyPositioned(coords)){
		return container->getArmyAt(coords)->GetOwner();
	}
	return id;
}
