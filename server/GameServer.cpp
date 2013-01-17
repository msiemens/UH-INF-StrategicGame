/*
 * GameServer.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include <iostream>

#include "GameEngine.h"
#include "gamemodel/GameMapServer.h"
#include <gamemodel/Player.h>
#include <list>

using namespace std;

int main(int argc, char* argv[]) {
	GameMapServer map;
	GameContainer container;

	GameEngine engine(&map, &container);

	engine.run();

	return 0;
}

