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

GameEngine::GameEngine(GameMap *m) {
	// TODO Auto-generated constructor stub
	isRunning=true;
	map=*m;
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

bool GameEngine::onPlayerConnect(Player player){
	playerlist.insert(playerlist.begin(),player);
	return true;
}

void GameEngine::onPlayerDisconnect(Player player){
	playerlist.remove(player);
}

void GameEngine::onPlayerAction(Player player,GameAction action){

	if(logic.checkPlayerAction(player,action)==true){
		doAction(player,action);
	}

}

void GameEngine::doAction(Player player,GameAction action){
	ARecruit* recruit = dynamic_cast<ARecruit>(action);
	AMove* move = dynamic_cast<AMove>(action);
	ABuild* build = dynamic_cast<ABuild>(action);
	AAttack* attack=dynamic_cast<AAttack>(action);

	if(recruit!=0){

		ARecruit recruit;

	}
	if(move!=0){
		EArmy* army=dynamic_cast<EArmy>(move->what);

		army->setPosition(move->to);

		map.setArmy(move->to);
	}
	if(build!=0){
		GameEntity building=build->what;
		EPlace where=build->where;
		where.addBuilding(building);
	}
	if(attack!=0){

	}

	//GameNetwork.broadcast(action);

}

