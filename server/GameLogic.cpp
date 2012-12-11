/*
 * GameLogic.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */

#include <list>
#include <string>

#include <server/GameLogic.h>
#include <server/GameMap.h>
#include <gamemodel/Player.h>
#include <gamemodel/GameAction.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/ABuild.h>
#include <gamemodel/actions/AAttack.h>
#include <gamemodel/ressources/RMoney.h>

GameLogic::GameLogic(GameMap map, list<Player> playerlist) :
		map(map), playerlist(playerlist) {
	// TODO Auto-generated constructor stub
}

GameLogic::~GameLogic() {
	// TODO Auto-generated destructor stub
}

//returns whose Army is positioned at coords
int GameLogic::whoseArmy(coordinates coords) {
	int playerid;
	/* for (Player p : playerlist) {
	 for (EArmy a : p.armies) {
	 if (a.getPosition() == coords) {
	 playerid = p.getPlayerId();
	 }
	 }
	 } */ // C++ is not Java ;)
	return playerid;
}

//return whose Place is at coords
int GameLogic::whosePlace(coordinates coords) {
	int playerid;
	/* for (Player p : playerlist) {
	 for (EPlace pl : p.places) {

	 }
	 } */
	return playerid;
}
//checks whether PlacerAction is valid or not
bool GameLogic::checkPlayerAction(Player player, GameAction action) {
	bool valid = false;

	ARecruit* recruit = dynamic_cast<ARecruit*>(&action);
	AMove* move = dynamic_cast<AMove*>(&action);
	ABuild* build = dynamic_cast<ABuild*>(&action);
	AAttack* attack = dynamic_cast<AAttack*>(&action);
//recruit
	if (recruit != 0) {
		// valid = (player.has(RMoney) >= recruit->costs) ? true : false;
		// TODO: player.has[RMoney] geht nicht. Was meinst du damit?
	}
//move
	else if (move != 0) {
		coordinates coords = move->to;
		valid = map.isWalkable(coords);

	}
//build
	else if (build != 0) {
		// valid = (player.has[RMoney] >= build->costs) ? true : false;
		// TODO: player.has[RMoney] geht nicht. Was meinst du damit?
	}
//attack
	else if (attack != 0) {
		coordinates coords = attack->where;
		/* if (*map.isArmyPositioned(coords)) {
		 int playerid = whoseArmy(coords);
		 valid = (playerid != player.getPlayerId()) ? true : false;
		 } */
	}

	return valid;
}

