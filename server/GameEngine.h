/*
 * GameEngine.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

#include <list>
#include "gamemodel/Player.h"
#include "gamemodel/GameAction.h"
#include "GameLogic.h"


using namespace std;

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	bool gameIsRunning();


	bool onPlayerConnect(Player player);
	void onPlayerDisconnect(Player player);
	void onPlayerAction(Player player,GameAction action);
	void doAction(Player player,GameAction action);

	GameLogic logic;


private:
	bool isRunning;
	list<Player> playerlist;
	int playercount;
};

#endif /* GAMEENGINE_H_ */
