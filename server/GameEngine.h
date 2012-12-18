/*
 * GameEngine.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <list>

#include <network/ServerNetwork.h>

#include "GameLogic.h"

class Player;
class GameMap;

using namespace std;

class GameEngine {
public:
	GameEngine(GameMap *map, list<PlayerPtr> *playerlist);
	virtual ~GameEngine();

	bool gameIsRunning();

	bool onPlayerConnect(PlayerPtr player);
	void onPlayerDisconnect(PlayerPtr player);
	void onPlayerAction(/*PlayerPtr player,*/  GameActionPtr action);
	void doAction(PlayerPtr player, GameActionPtr action);

	void test();
	void run();

	GameMap *map;
	GameLogic logic;

	PlayerPtr player;


	bool isRunning;
private:
	list<PlayerPtr> *playerlist;

	ServerNetwork m_network;
};

#endif /* GAMEENGINE_H_ */
