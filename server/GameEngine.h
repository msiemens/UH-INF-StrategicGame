/*
 * GameEngine.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

<<<<<<< HEAD
#include <list>

#include "GameLogic.h"

class Player;
class GameMap;

using namespace std;

class GameEngine {
public:
	GameEngine(GameMap *map, list<PlayerPtr> playerlist);
	virtual ~GameEngine();

	bool gameIsRunning();

	bool onPlayerConnect(PlayerPtr player);
	void onPlayerDisconnect(PlayerPtr player);
	void onPlayerAction(PlayerPtr player, GameActionPtr action);
	void doAction(PlayerPtr player, GameActionPtr action);

	void test();

	GameMap *map;
	GameLogic logic;

private:
	bool isRunning;
	list<PlayerPtr> playerlist;
=======
class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();
>>>>>>> tmp/client
};

#endif /* GAMEENGINE_H_ */
