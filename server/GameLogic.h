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
#include <gamemodel/GameMap.h>
#include <server/GameContainer.h>

using namespace std;

class GameLogic {
public:
	GameLogic(GameMap *map, GameContainer *container);
	virtual ~GameLogic();

	bool checkPlayerAction(PlayerPtr player, GameActionPtr action);

private:
	GameMap *map;
	GameContainer *container;
};

#endif /* GAMELOGIC_H_ */
