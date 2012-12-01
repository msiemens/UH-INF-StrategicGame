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

}

GameMap::~GameMap() {
	// TODO Auto-generated destructor stub
}

void GameMap::setWalkable(coordinates coords){
	map[coords.y][coords.x]=map[coords.y][coords.x]|walkable;
}

void GameMap::setWalkable(int x,int y){
	map[y][x]=map[y][x]|walkable;
}

void GameMap::setArmy(coordinates coords){
	map[coords.y][coords.x]=map[coords.y][coords.x]|army;
}

void GameMap::setArmy(int x,int y){
	map[y][x]=map[y][x]|army;
}

void GameMap::setPlace(coordinates coords){
	map[coords.y][coords.x]=map[coords.y][coords.x]|place;
}

void GameMap::setPlace(int x,int y){
	map[y][x]=map[y][x]|place;
}

void GameMap::setBlocked(coordinates coords){
	map[coords.y][coords.x]=blocked;
}

void GameMap::setBlocked(int x,int y){
	map[y][x]=blocked;
}

bool GameMap::isWalkable(coordinates coords){
	return (map[coords.x][coords.y] & walkable)?true:false;
}

bool GameMap::isArmyPositioned(coordinates coords){
	return (map[coords.x][coords.y] & army)?true:false;
}

bool GameMap::isPlace(coordinates coords){
	return (map[coords.x][coords.y] & place)?true:false;
}






} /* namespace std */
