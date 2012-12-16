/*
 * GameLogic.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include <list>

#include <gamemodel/GameAction.h>
#include <gamemodel/Player.h>
#include <gamemodel/utils/coordinates.h>


#include "GameMap.h"


using namespace std;

class GameLogic {
public:
	GameLogic(GameMap *map, list<PlayerPtr> playerlist);
	virtual ~GameLogic();

	bool checkPlayerAction(PlayerPtr player, GameActionPtr action);

	int whoseArmy(coordinates coords);
	int whosePlace(coordinates coords);

private:
	GameMap *map;
	list<PlayerPtr> playerlist;
};

#endif /* GAMELOGIC_H_ */
