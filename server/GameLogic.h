/*
 * GameLogic.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

#include "gamemodel/Player.h"
#include "gamemodel/GameAction.h"
#include "server/GameMap.h"
#include "gamemodel/Player.h"

class GameLogic {
public:
	GameLogic(GameMap *m,list<Player> *p);
	virtual ~GameLogic();

	bool checkPlayerAction(Player player,GameAction action);

	int whoseArmy(coordinates coords);
	int whosePlace(coordinates coords);


private:
	GameMap &map;
	list<Player> &playerlist;
};

#endif /* GAMELOGIC_H_ */
