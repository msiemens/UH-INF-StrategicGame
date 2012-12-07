/*
 * GameMap.cpp
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#include "server/GameMap.h"

namespace std {

GameMap::GameMap() {
	// TODO Auto-generated constructor stub
	for(int i=0;i<4;i++){
		for(int u=0;u<4;u++){
			setWalkable(i,u);
		}
	}

	setArmy(2,3);
	setPlace(1,2);
}

GameMap::~GameMap() {
	// TODO Auto-generated destructor stub
}

void GameMap::setWalkable(coordinates coords) {
	setWalkable(coords.x, coords.y);
}

void GameMap::setWalkable(int x, int y) {
	map[y][x] = map[y][x] | walkable;
}

void GameMap::setArmy(int x, int y) {
	map[y][x] = map[y][x] | army;
}

void GameMap::setArmy(coordinates coords) {
	setArmy(coords.x, coords.y);
}

void GameMap::setPlace(int x, int y) {
	map[y][x] = map[y][x] | place;
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
	return (map[coords.x][coords.y] & army) ? true : false;
}

bool GameMap::isPlace(coordinates coords) {
	return (map[coords.x][coords.y] & place) ? true : false;
}

} /* namespace std */
