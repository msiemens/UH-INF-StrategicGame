/*
 * GameServer.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include <iostream>

#include "GameEngine.h"
#include "GameMap.h"
#include <gamemodel/Player.h>
#include <list>

int main(int argc, char* argv[]) {
	GameMap map;
	list<PlayerPtr> playerlist;
	GameEngine engine(&map, playerlist);
	return 0;
}

