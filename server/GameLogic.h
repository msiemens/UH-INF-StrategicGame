/*
 * GameLogic.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include <list>

#include "GameMap.h"

class GameAction;
class Player;
class coordinates;

using namespace std;

class GameLogic {
public:
	GameLogic(GameMap *map, list<Player> *playerlist);
	virtual ~GameLogic();

	bool checkPlayerAction(Player *player, GameAction *action);

	int whoseArmy(coordinates coords);
	int whosePlace(coordinates coords);

private:
	GameMap *map;
	list<Player> *playerlist;
};

#endif /* GAMELOGIC_H_ */
