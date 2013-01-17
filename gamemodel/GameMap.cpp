/*
 * GameMap.cpp
 *
 * Created on: 30.11.2012
 * Author: Henrik
 */

#include <iostream>
#include <gamemodel/entities/ELocation.h>
#include "GameMap.h"

using namespace std;

GameMap::GameMap() {
	editMode = false;
	mapSizeX = 64;
	mapSizeY = 48;
	createMapFromTxt("client/maps/map3.txt");
}

GameMap::~GameMap() {
}


void GameMap::setWalkable(coordinates coords) {
	setWalkable(coords.x, coords.y);
}

void GameMap::setWalkable(int x, int y) {
	map[y][x] = walkable;
}

void GameMap::setArmy(int x, int y) {
	map[y][x] = army;
}

void GameMap::setArmy(coordinates coords) {
	setArmy(coords.x, coords.y);
}

void GameMap::setPlace(int x, int y) {
	map[y][x] = place;
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

void GameMap::setStartBase(int x, int y){
	map[y][x] = startbase;
}

void GameMap::setStartBase(coordinates coords){
	setStartBase(coords.y,coords.x);
}

bool GameMap::isBlocked(coordinates coords) {
	return (map[coords.y][coords.x] & blocked) ? true : false;
}
bool GameMap::isWalkable(coordinates coords) {
	return (map[coords.y][coords.x] & walkable) ? true : false;
}

bool GameMap::isArmyPositioned(coordinates coords) {
	return (map[coords.y][coords.x] & army) ? true : false;
}

bool GameMap::isPlace(coordinates coords) {
	return (map[coords.y][coords.x] & place) ? true : false;
}

bool GameMap::isStartBase(coordinates coords){
	return (map[coords.y][coords.x] & startbase)? true : false;
}

void GameMap::createMapFromTxt(string path) {
	ifstream in(path);

	mapSizeY = 1;
	mapSizeX = 0;

	int x = 0;
	int y = 0;

	if (!in.is_open()) {
		cerr << "File not found: " << path << endl;
		return;
	}

	while (in.eof() != true) {
		char c = in.get();
			if (c == '\n') {
				mapSizeY++;
				y++;
				mapSizeX = 0;
				x = 0;
			} else if (c == 's'){
				setStartBase(x,y);
				x++;
			} else if (c == 'w') {
				setWalkable(x, y);
				x++;
			} else if (c == 'p') {
				setPlace(x, y);
				x++;
			}  else {
				setBlocked(x, y);
				x++;
			}
		mapSizeX++;
	}
}

void GameMap::printMapStatus() {
	coordinates coords;
	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			coords.x = x;
			coords.y = y;
			if (isArmyPositioned(coords)) {
				cout << "a";
			} else if (isWalkable(coords)) {
				cout << "w";
			} else if (isPlace(coords)) {
				cout << "p";
			}else if(isStartBase(coords)){
				cout << "s";
			}else if (isBlocked(coords)) {
				cout << "b";
			}
		}
		cout << "\n";
	}
}
