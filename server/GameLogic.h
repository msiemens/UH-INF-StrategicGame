/*
 * GameLogic.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_

<<<<<<< HEAD
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

	boost::uuids::uuid whoseArmy(coordinates coords);
	boost::uuids::uuid whosePlace(coordinates coords);

private:
	GameMap *map;
	list<PlayerPtr> playerlist;
=======
class GameLogic {
public:
	GameLogic();
	virtual ~GameLogic();
>>>>>>> tmp/client
};

#endif /* GAMELOGIC_H_ */
