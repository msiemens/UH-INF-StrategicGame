/*
 * GameMap.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef GAMEMAP_H_
#define GAMEMAP_H_

#include <gamemodel/utils/coordinates.h>

class GameMap {
public:
	GameMap();
	virtual ~GameMap();

	unsigned char map[4][4];

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
	bool isArmyPositioned(coordinates coords);
	bool isPlace(coordinates coords);

};

#endif /* GAMEMAP_H_ */
