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

#include <boost/uuid/uuid.hpp>

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

GameLogic::GameLogic(GameMap *map, list<PlayerPtr> *playerlist) :
		map(map),
		playerlist(playerlist) {
}

GameLogic::~GameLogic() {
}

//returns whose Army is positioned at coords
boost::uuids::uuid GameLogic::whoseArmy(coordinates coords) {
	boost::uuids::uuid playerId;

	for (auto player : *playerlist) {
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
boost::uuids::uuid GameLogic::whosePlace(coordinates coords) {
	boost::uuids::uuid playerId;

	for (auto player : *playerlist) {
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
	std::cout << "------------------------------\n";
	cout << "GameLogic::checkPlayerAction(...)" << endl;
	bool valid = false;

	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	AMove* move = dynamic_cast<AMove*>(action.get());
	ABuild* build = dynamic_cast<ABuild*>(action.get());
	AAttack* attack = dynamic_cast<AAttack*>(action.get());

//recruit
	if (recruit != NULL) {
		GameRessourcePtr costs(recruit->costs);
		EUnitPtr troops(recruit->what);
		ELocationPtr base(recruit->base);

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
		ELocationPtr where(build->where);

		valid = true;
	}
//attack
	else if (attack != NULL) {
		cout << 4 << endl;
		GameEntityPtr what(attack->what);
		coordinates where = attack->where;

		if (map->isArmyPositioned(where)) {
			valid = (player->getPlayerId() != whoseArmy(where)) ? true : false;
		} else {
			std::cout << "Auf " << where.x << "/" << where.y
					<< " ist keine Armee positioniert\n";
		}

	}

	return valid;
}

