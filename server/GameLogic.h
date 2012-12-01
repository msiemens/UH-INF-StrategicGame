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

class GameLogic {
public:
	GameLogic();
	virtual ~GameLogic();

	bool checkPlayerAction(Player player,GameAction action);

	int whoseArmy(coordinates coords);
	int whosePlace(coordinates coords);


private:
	GameMap map;
};

#endif /* GAMELOGIC_H_ */
