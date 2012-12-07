/*
 * GameServer.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include "server/GameServer.h"

GameServer::GameServer() {
	// TODO Auto-generated constructor stub


	logic(map);
	engine(logic,map);
}

GameServer::~GameServer() {
	// TODO Auto-generated destructor stub
}

int main(){
	GameServer server;
}

