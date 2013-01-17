/*
* GameMap.h
*
* Created on: 30.11.2012
* Author: Henrik
*/

#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include <list>
#include <fstream>
#include <string>
#include <boost/uuid/uuid.hpp>
#include <gamemodel/utils/coordinates.h>
#include <gamemodel/entities/ELocation.h>
#include <gamemodel/Player.h>


class GameMap {
public:
GameMap();
virtual ~GameMap();

unsigned char map[768][1024];

enum attributes {
	// 0x01 ==   1 == "00000001"
	// 0x02 ==   2 == "00000010"
	// 0x04 ==   4 == "00000100"
	// 0x08 ==   8 == "00001000"
	// 0x10 ==  16 == "00010000"
	// 0x20 ==  32 == "00100000"
	// 0x40 ==  64 == "01000000"
	// 0x80 == 128 == "10000000"

walkable = 0x01, blocked = 0x02, place = 0x04, army = 0x08, startbase=0x10
};

boost::uuids::uuid whosePlace(coordinates coords);

void setWalkable(coordinates coords);
void setWalkable(int x, int y);

void setArmy(coordinates coords);
void setArmy(int x, int y);

void setPlace(coordinates coords);
void setPlace(int x, int y);

void setBlocked(coordinates coords);
void setBlocked(int x, int y);

void setStartBase(coordinates coords);
void setStartBase(int x, int y);

bool isWalkable(coordinates coords);
bool isBlocked(coordinates coords);
bool isArmyPositioned(coordinates coords);
bool isPlace(coordinates coords);
bool isStartBase(coordinates coords);



bool editMode;

void createMapFromTxt(std::string path);

void printMapStatus();

int getClickPosX(int x);
int getClickPosY(int y);

ELocationPtr getPlaceAt(coordinates coords);
list<ELocationPtr> placeList;

int mapSizeX;
int mapSizeY;

};

#endif /* GAMEMAP_H_ */
