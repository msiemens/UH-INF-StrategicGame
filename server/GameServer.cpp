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
	std::cout << "start\n";
	GameMap map;
	GameEngine engine(&map);
	return 0;
}

