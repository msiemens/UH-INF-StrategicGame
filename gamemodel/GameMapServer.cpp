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
				container->addLocation(location);			}
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
	if(this->isPlace(coords) or this->isStartBase(coords)){
			for(int i=0;i<container->getLocationCount();i++){
				ELocationPtr location(container->getLocation(i));
				if(location->getCoords().x==coords.x and location->getCoords().y==coords.y){
					return location;
				}
			}
		}
}

boost::uuids::uuid GameMapServer::whoseLocationAt(coordinates coords) {
	if(this->isPlace(coords)){
		return getLocationAt(coords)->GetOwner();
	}
}
//
//EArmyPtr GameMapServer::getArmyAt(coordinates coords) {
//	if(this->isArmyPositioned(coords)){
//		cout << "====================================1" << endl;
//
//		cout << "size: "  << container->armylist.size() << endl;
//		cout << "size: "  << container->getArmyCount() << endl;
//		for(int i=0;i<container->getArmyCount();i++){
//			cout << "i:" << i << endl;
//			EArmyPtr army(container->getArmy(i));
//			cout << "x:" << army->getCoords().x << endl;
//			if(army->getCoords().x==coords.x and army->getCoords().y==coords.y){
//				cout << "====================================2" << endl;
//				return army;
//			}
//		}
//	}
//}

boost::uuids::uuid GameMapServer::whoseArmyAt(coordinates coords) {
	if(this->isArmyPositioned(coords)){
		container->getArmyAt(coords)->GetOwner();
	}
}
