/*
 * GameLogic.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include <list>
#include <string>
#include <iostream>

#include <server/GameLogic.h>
#include <server/GameMap.h>
#include <gamemodel/Player.h>
#include <gamemodel/GameAction.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/ABuild.h>
#include <gamemodel/actions/AAttack.h>

#include <gamemodel/ressources/RMoney.h>

GameLogic::GameLogic(GameMap *map, list<Player> *playerlist) :
		map(map), playerlist(playerlist) {
}

GameLogic::~GameLogic() {
	// TODO Auto-generated destructor stub
}

//returns whose Army is positioned at coords
int GameLogic::whoseArmy(coordinates coords) {
	int playerid=99;


	return playerid;
}

//return whose Place is at coords
int GameLogic::whosePlace(coordinates coords) {
	int playerid;
	return playerid;
}
//checks whether PlacerAction is valid or not
bool GameLogic::checkPlayerAction(Player *player, GameAction *action) {

	bool valid = false;

	ARecruit* recruit = dynamic_cast<ARecruit*>(action);
	AMove* move = dynamic_cast<AMove*>(action);
	ABuild* build = dynamic_cast<ABuild*>(action);
	AAttack* attack = dynamic_cast<AAttack*>(action);

//recruit
	if (recruit != NULL) {
		GameRessource costs=recruit->costs;
		ETroops troops=recruit->what;
		EPlace base=recruit->base;

		valid=true;
	}
//move
	else if (move != NULL) {
		GameEntity what=move->what;
		coordinates to=move->to;

		valid=(map->isWalkable(to))?true:false;
	}
//build
	else if (build != NULL) {
		GameRessource costs=build->costs;
		EBuilding building=build->what;
		EPlace where=build->where;

		valid=true;
	}
//attack
	else if (attack != NULL) {
		GameEntity what=attack->what;
		coordinates where=attack->where;

		if(map->isArmyPositioned(where)){
			valid=(player->getPlayerId()!=whoseArmy(where))?true:false;
		}


	}

	return valid;
}

