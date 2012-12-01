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

GameLogic::GameLogic() {
	// TODO Auto-generated constructor stub
}

GameLogic::~GameLogic() {
	// TODO Auto-generated destructor stub
}

int GameLogic::whoseArmy(coordinates coords){
	return 0;
}

int GameLogic::whosePlace(coordinates coords){
	return 0;
}

bool GameLogic::checkPlayerAction(Player player, GameAction action) {
	bool ret = false;

	ARecruit* recruit = dynamic_cast<ARecruit>(action);
	AMove* move = dynamic_cast<AMove>(action);
	ABuild* build = dynamic_cast<ABuild>(action);
	AAttack* attack = dynamic_cast<AAttack>(action);
//recruit
	if (recruit != 0) {
		ret = (player.has[0] > recruit->costs) ? true : false;
	}
//move
	else if (move != 0) {
		coordinates coords = move->to;

		ret = map.isMovable(coords);
	}
//build
	else if (build != 0) {
		if (player.has[0] > build->costs) {
		}
	}
//attack
	else if (attack != 0) {
		coordinates coords;
		if(map.isArmyPositioned(coords)){
			ret=(whoseArmy()==player->id)?false:true;
		}
	}

	return ret;
}



