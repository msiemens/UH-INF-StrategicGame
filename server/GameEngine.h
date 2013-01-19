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

#include <server/GameContainer.h>
#include "GameLogic.h"

class Player;

using namespace std;

class GameEngine {
public:
	GameEngine(GameMapServer *map, GameContainer *container);
	virtual ~GameEngine();

	bool gameIsRunning();

	bool onPlayerConnect(PlayerPtr player);
	void onPlayerDisconnect(PlayerPtr player);
	void onPlayerAction(GameActionPtr action, PlayerPtr player);
	void doAction(PlayerPtr player, GameActionPtr action);

    GameActionPtr onPlayerRecruit(PlayerPtr player,ARecruitPtr recruit);
    GameActionPtr onPlayerMove(PlayerPtr player,AMovePtr move);
    GameActionPtr onPlayerBuild(PlayerPtr player,ABuildPtr build);
    GameActionPtr onPlayerAttack(PlayerPtr player,AAttackPtr attack);
    GameActionPtr onPlayerSetAP(PlayerPtr player,ASetAPPtr setap);
    void onPlayerSetTurn(PlayerPtr player,ASetTurnPtr setturn);
    GameActionPtr onPlayerLogIn(PlayerPtr player,ALogInPtr logIn);

	void BroadcastAction(GameActionPtr action);

	void createArmyAt(coordinates coords,PlayerPtr owner);

	void onNextTurn();

	void startSession();

	void run();

	GameMapServer *map;
	GameLogic logic;
	GameContainer *container;

	bool isRunning;
private:
	ServerNetwork m_network;
};

#endif /* GAMEENGINE_H_ */
