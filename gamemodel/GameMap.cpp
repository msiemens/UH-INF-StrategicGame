/*
 * GameMap.cpp
 *
 * Created on: 30.11.2012
 * Author: Henrik
 */

#include "GameMap.h"
#include <iostream>
#include <gamemodel/entities/ELocation.h>
using namespace std;

GameMap::GameMap() {
	editMode = false;
	mapSizeX = 64;
	mapSizeY = 48;
	createMapFromTxt(
			"C:/GameDev/Projekte/UH-INF-StrategicGame.build/client/maps/map3.txt");
	createPlaces();
	//printMapStatus();
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

void GameMap::createPlaces() {

	int counter = 0;
	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			if (isPlace(coordinates(x, y))) {
				ELocationPtr place(new ELocation);
				place->setCoords(x, y);
				place->setImgPath("client/gfx/entity/village.png");
				place->setIconPath("client/gfx/entity/icons/castle.png");
				placeList.insert(placeList.begin(), place);
			}
		}
	}
}

ELocationPtr GameMap::getPlaceAt(coordinates coords) {
	ELocationPtr placeAt;
	for (auto place : placeList) {
		coordinates placeCoords = place->getCoords();
		if (placeCoords.x == coords.x and placeCoords.y == coords.y) {
			placeAt = place;
		}
	}
	return placeAt;
}

int GameMap::getClickPosX(int x){
	int posx=0;

	posx =x/20;

	return posx;
}
int GameMap::getClickPosY(int y){
	int posy=0;

	posy =y/20;

	return posy;
}
void GameMap::createMapFromTxt(string path) {
	ifstream in(path);

	mapSizeY = 1;
	mapSizeX = 0;

	int x = 0;
	int y = 0;

	while (in.eof() != true) {
		char c = in.get();
			if (c == '\n') {
				mapSizeY++;
				y++;
				mapSizeX = 0;
				x = 0;
			} else if (c == 'w') {
				setWalkable(x, y);
				x++;
			} else if (c == 'p') {
				setPlace(x, y);
				x++;
			} else {
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
			}else if (isBlocked(coords)) {
				cout << "b";
			}
		}
		cout << "\n";
	}
}