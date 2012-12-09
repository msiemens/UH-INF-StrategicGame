/*
 * GameServer.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include <iostream>

#include "server/GameServer.h"
#include "server/GameMap.h"
#include "server/GameEngine.h"

GameServer::GameServer() {
	// TODO Auto-generated constructor stub
	std::cout << "server started\n";

}

GameServer::~GameServer() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char* argv[]){
	std::cout<<"start";
	GameServer server;
	GameMap map;
	GameEngine engine(map);
	return 0;
}

