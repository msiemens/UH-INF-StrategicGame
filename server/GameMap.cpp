/*
 * GameMap.cpp
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#include "GameMap.h"
#include <iostream>

GameMap::GameMap() {
	for (int i = 0; i < 4; i++) {
		for (int u = 0; u < 4; u++) {
			setWalkable(i, u);
		}
	}

}

GameMap::~GameMap() {
}

void GameMap::setWalkable(coordinates coords) {
	setWalkable(coords.x, coords.y);
}

void GameMap::setWalkable(int x, int y) {
	if(isPlace(coordinates(x,y))==false){
		map[y][x] = /*map[y][x]*/  walkable;
	}
}

void GameMap::setArmy(int x, int y) {
	map[y][x] =  army;
}

void GameMap::setArmy(coordinates coords) {
	setArmy(coords.x, coords.y);
}

void GameMap::setPlace(int x, int y) {
	map[y][x] =  place;
}

void GameMap::setPlace(coordinates coords) {
	setPlace(coords.x, coords.y);
}

void GameMap::setBlocked(int x, int y) {
	map[y][x] = blocked;
}

void GameMap::setBlocked(coordinates coords) {
	setBlocked(coords.x, coords.y);
}

bool GameMap::isWalkable(coordinates coords) {
	return (map[coords.x][coords.y] & walkable) ? true : false;
}

bool GameMap::isArmyPositioned(coordinates coords) {
	if(map[coords.x][coords.y] & army){
	std::cout << "isArmyasda";
	}
	return (map[coords.x][coords.y] & army) ? true : false;
}

bool GameMap::isPlace(coordinates coords) {
	return (map[coords.x][coords.y] & place) ? true : false;
}

void GameMap::printMapStatus(){
	coordinates coords;
	for(int i=0;i<4;i++){
		for(int u=0;u<4;u++){
			coords.x=u;
			coords.y=i;
			if(isArmyPositioned(coords)){
				std::cout << "a ";
			}else if(isWalkable(coords)){
				std::cout << "w ";
			}else if(isPlace(coords)){
				std::cout << "p ";
			}
		}
		std::cout << "\n";
	}
}
