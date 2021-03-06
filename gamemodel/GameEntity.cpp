/*
 * GameEntity.cpp
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#include "GameEntity.h"
using namespace std;

GameEntity::GameEntity() :
		cost(0),
		coords() {

}
void GameEntity::setCoords(int x, int y) {
	coords.x = x;
	coords.y = y;
}

void GameEntity::setCoords(coordinates coords) {
	setCoords(coords.x, coords.y);
}

coordinates GameEntity::getCoords() {
	return coords;
}

string GameEntity::getImgPath() {
	return this->imgpath;
}
void GameEntity::setImgPath(string path) {
	this->imgpath = path;
}
