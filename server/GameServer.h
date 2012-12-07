/*
 * GameServer.h
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#ifndef GAMESERVER_H_
#define GAMESERVER_H_

#include "server/GameMap.h"

class GameServer {
public:
	GameServer();
	virtual ~GameServer();


	GameEngine engine;
};

#endif /* GAMESERVER_H_ */
