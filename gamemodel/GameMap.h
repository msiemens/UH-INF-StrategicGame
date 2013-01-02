/*
* GameMap.h
*
* Created on: 30.11.2012
* Author: Henrik
*/

#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include <gamemodel/utils/coordinates.h>
#include <list>
#include <gamemodel/entities/EPlace.h>
#include <boost/uuid/uuid.hpp>
#include <fstream>
#include <string>


class GameMap {
public:
GameMap();
virtual ~GameMap();

unsigned char map[768][1024];

enum attributes {
walkable = 0x01, blocked = 0x02, place = 0x04, army = 0x08
};

void setWalkable(coordinates coords);
void setWalkable(int x, int y);

void setArmy(coordinates coords);
void setArmy(int x, int y);

void setPlace(coordinates coords);
void setPlace(int x, int y);

void setBlocked(coordinates coords);
void setBlocked(int x, int y);

bool isWalkable(coordinates coords);
bool isBlocked(coordinates coords);
bool isArmyPositioned(coordinates coords);
bool isPlace(coordinates coords);
bool editMode;

void createMapFromTxt(std::string path);

void printMapStatus();
void createPlaces();

int getClickPosX(int x);
int getClickPosY(int y);
EPlacePtr getPlaceAt(coordinates coords);

std::list<EPlacePtr> placeList;

int mapSizeX;
int mapSizeY;

};

#endif /* GAMEMAP_H_ */
