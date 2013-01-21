/*
 * GameServer.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include <iostream>

#include "GameEngine.h"
#include "gamemodel/GameMap.h"
#include <gamemodel/Player.h>
#include <list>

using namespace std;

int main(int argc, char* argv[]) {
	GameMap map;
	list<PlayerPtr> playerlist;
	GameEngine engine(&map, &playerlist);

	engine.run();

	return 0;
}

