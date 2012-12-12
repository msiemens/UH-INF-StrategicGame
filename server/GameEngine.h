/*
 * GameEngine.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <list>
#include "GameLogic.h"

class Player;
class GameAction;
class GameMap;

using namespace std;

class GameEngine {
public:
	GameEngine(GameMap *map);
	virtual ~GameEngine();

	bool gameIsRunning();

	bool onPlayerConnect(Player player);
	void onPlayerDisconnect(Player player);
	void onPlayerAction(Player player, GameAction *action);
	void doAction(Player player, GameAction *action);

	void test();

	GameMap *map;
	GameLogic logic;

private:
	bool isRunning;
	list<Player> playerlist;
};

#endif /* GAMEENGINE_H_ */
