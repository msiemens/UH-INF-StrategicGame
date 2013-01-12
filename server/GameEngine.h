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
#include <gamemodel/GameMap.h>

#include "GameLogic.h"

class Player;
//class GameMap;

using namespace std;

class GameEngine {
public:
	GameEngine(GameMap *map, list<PlayerPtr> *playerlist);
	virtual ~GameEngine();

	bool gameIsRunning();

	bool onPlayerConnect(PlayerPtr player);
	void onPlayerDisconnect(PlayerPtr player);
	void onPlayerAction(GameActionPtr action, PlayerPtr player);
	void doAction(PlayerPtr player, GameActionPtr action);

	void createArmyAt(coordinates coords,PlayerPtr owner);

	void test();
	void run();

	GameMap *map;
	GameLogic logic;

	bool isRunning;
private:
	list<PlayerPtr> *playerlist;

	ServerNetwork m_network;
};

#endif /* GAMEENGINE_H_ */
