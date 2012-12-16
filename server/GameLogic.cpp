/*
 * GameLogic.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include <list>
#include <string>
#include <iostream>
#include <typeinfo>

#include <server/GameLogic.h>
#include <server/GameMap.h>
#include <gamemodel/Player.h>
#include <gamemodel/GameAction.h>
#include <gamemodel/entities/EArmy.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/ABuild.h>
#include <gamemodel/actions/AAttack.h>

#include <gamemodel/ressources/RMoney.h>

GameLogic::GameLogic(GameMap *map, list<PlayerPtr> playerlist) :
		map(map),
		playerlist(playerlist) {
}

GameLogic::~GameLogic() {
	// TODOAuto-generated destructor stub
}

//returns whose Army is positioned at coords
int GameLogic::whoseArmy(coordinates coords) {
	int playerId = 0;

	std::cout << "\nCoord.x=" << coords.x << " Coord.y=" << coords.y << "\n";

	for (auto player : playerlist) {
		for (auto army : player->armies) {
			coordinates pos = army->getCoords();

			if (pos.x == coords.x && pos.y == coords.y) {
				playerId = player->getPlayerId();
			}
		}
	}

	return playerId;
}

//return whose Place is at coords
int GameLogic::whosePlace(coordinates coords) {
	int playerId;

	for (auto player : playerlist) {
		for (auto place : player->places) {
			coordinates pos = place->getCoords();
			if (pos.x == coords.x && pos.y == coords.y) {
				playerId = player->getPlayerId();
			}
		}
	}

	return playerId;
}
//checks whether PlacerAction is valid or not
bool GameLogic::checkPlayerAction(PlayerPtr player, GameActionPtr action) {

	bool valid = false;

	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	AMove* move = dynamic_cast<AMove*>(action.get());
	ABuild* build = dynamic_cast<ABuild*>(action.get());
	AAttack* attack = dynamic_cast<AAttack*>(action.get());

//recruit
	if (recruit != NULL) {
		GameRessourcePtr costs(recruit->costs);
		ETroopsPtr troops(recruit->what);
		EPlacePtr base(recruit->base);

		valid = true;
	}
//move
	else if (move != NULL) {
		GameEntityPtr what(move->what);
		coordinates to = move->to;

		valid = (map->isWalkable(to)) ? true : false;
	}
//build
	else if (build != NULL) {
		GameRessourcePtr costs(build->costs);
		EBuildingPtr building(build->what);
		EPlacePtr where(build->where);

		valid = true;
	}
//attack
	else if (attack != NULL) {
		GameEntityPtr what(attack->what);
		coordinates where = attack->where;

		bool b = map->isArmyPositioned(where);

		int playerId = whoseArmy(where);

		if (b == 0) {
			valid = (player->getPlayerId() != whoseArmy(where)) ? true : false;
		}

	}

	return valid;
}

