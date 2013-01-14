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

#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ABuild.h>
#include <gamemodel/actions/AAttack.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>
#include <gamemodel/actions/ALogIn.h>

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

	GameActionPtr onPlayerRecruit(PlayerPtr player,ARecruit* recruit);
	GameActionPtr onPlayerMove(PlayerPtr player,AMove* move);
	GameActionPtr onPlayerBuild(PlayerPtr player,ABuild* build);
	GameActionPtr onPlayerAttack(PlayerPtr player,AAttack* attack);
	GameActionPtr onPlayerSetAP(PlayerPtr player,ASetAP* setap);
	void onPlayerSetTurn(PlayerPtr player,ASetTurn* setturn);
	GameActionPtr onPlayerLogIn(PlayerPtr player,ALogIn* logIn);

	void BroadcastAction(GameActionPtr action);

	void createArmyAt(coordinates coords,PlayerPtr owner);

	void onNextTurn();

	void startSession();

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
