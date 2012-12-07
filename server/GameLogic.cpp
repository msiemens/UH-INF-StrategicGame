/*
 * GameLogic.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include "server/GameLogic.h"
#include "gamemodel/GameAction.h"
#include "gamemodel/actions/AMove.h"
#include "gamemodel/actions/AAttack.h"
#include "server/GameMap.h"
#include <string>

GameLogic::GameLogic(GameMap *m,list<Player> *p) {
	// TODO Auto-generated constructor stub
	map=*m;
	playerlist=*p;
}

GameLogic::~GameLogic() {
	// TODO Auto-generated destructor stub
}

//returns whose Army is positioned at coords
int GameLogic::whoseArmy(coordinates coords){
	int playerid;
	for(Player p:playerlist){
		for(EArmy a:p.armies){
			if(a.getPosition()==coords){
				playerid=p.getPlayerId();
			}
		}
	}
	return playerid;
}

//return whose Place is at coords
int GameLogic::whosePlace(coordinates coords){
	int playerid;
	for(Player p:playerlist){
		for(EPlace pl:p.places){

		}
	}
	return playerid;
}
//checks whether PlacerAction is valid or not
bool GameLogic::checkPlayerAction(Player player, GameAction action) {
	bool valid = false;

	ARecruit* recruit = dynamic_cast<ARecruit>(action);
	AMove* move = dynamic_cast<AMove>(action);
	ABuild* build = dynamic_cast<ABuild>(action);
	AAttack* attack = dynamic_cast<AAttack>(action);
//recruit
	if (recruit != 0) {
		valid = (player.has[0] > recruit->costs) ? true : false;
	}
//move
	else if (move != 0) {
		coordinates coords = move->to;

		valid = *map.isWalkable(coords);

	}
//build
	else if (build != 0) {
		if (player.has[0] > build->costs) {
		}
	}
//attack
	else if (attack != 0) {
		coordinates coords=attack->where;
		if(*map.isArmyPositioned(coords)){
			int playerid=whoseArmy(coords);
			valid=(playerid!=player.getPlayerId())?true:false;
		}
	}

	return valid;
}



