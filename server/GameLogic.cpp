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
	std::cout << "\nlogic loaded";
}

GameLogic::~GameLogic() {
	// TODO Auto-generated destructor stub
}

//returns whose Army is positioned at coords
int GameLogic::whoseArmy(coordinates coords) {
	int playerid;
	return playerid;
}

//return whose Place is at coords
int GameLogic::whosePlace(coordinates coords) {
	int playerid;
	return playerid;
}
//checks whether PlacerAction is valid or not
bool GameLogic::checkPlayerAction(Player player, GameAction *action) {

	bool valid = true;

	ARecruit* recruit = dynamic_cast<ARecruit*>(action);
	AMove* move = dynamic_cast<AMove*>(action);
	ABuild* build = dynamic_cast<ABuild*>(action);
	AAttack* attack = dynamic_cast<AAttack*>(action);

//recruit
	if (recruit != NULL) {
		GameRessource ressource=recruit->costs;
		ETroops troops=recruit->what;
		EPlace base=recruit->base;

		valid=true;

		std::cout << "\nRecruit-Befehl an Logic übergeben.";
	}
//move
	else if (move != NULL) {

		std::cout << "\nMove-Befehl an Logic übergeben.";
	}
//build
	else if (build != NULL) {
		GameRessource costs=build->costs;
		EBuilding building=build->what;
		EPlace where=build->where;
		RMoney money;
		valid=true;
		std::cout << "\nBuild-Befehl an Logic übergeben.";
	}
//attack
	else if (attack != NULL) {
		std::cout << "\nAttack-Befehl an Logic übergeben.";
	}

	return valid;
}

