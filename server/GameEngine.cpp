/*
 * GameEngine.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include "server/GameEngine.h"
#include "gamemodel/Player.h"
#include "gamemodel/GameAction.h"

using namespace std;

GameEngine::GameEngine() {
	// TODO Auto-generated constructor stub
	isRunning=true;
	playercount=0;
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

bool GameEngine::onPlayerConnect(Player player){
	playerlist.insert(playerlist.begin(),player);
	playercount++;
	return true;
}

void GameEngine::onPlayerDisconnect(Player player){
	playerlist.remove(player);
}

void GameEngine::onPlayerAction(Player player,GameAction action){

	if(logic.checkPlayerAction(player,action)==true){
		createObject(player,action.what);
	}

}

void GameEngine::createObject(Player player,GameEntity object){
	player.addEntity(entity);
}

