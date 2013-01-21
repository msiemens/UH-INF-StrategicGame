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
#include <gamemodel/GameMapServer.h>
#include <server/GameContainer.h>

using namespace std;

class GameLogic {
public:
	GameLogic(GameMapServer *map, GameContainer *container);
	virtual ~GameLogic();

	bool checkPlayerAction(PlayerPtr player, GameActionPtr action);

private:
	GameMapServer *map;
	GameContainer *container;
};

#endif /* GAMELOGIC_H_ */
