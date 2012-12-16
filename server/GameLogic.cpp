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

GameLogic::GameLogic(GameMap *map, list<Player*> *playerlist) :
		map(map), playerlist(playerlist) {
}

GameLogic::~GameLogic() {
	// TODOAuto-generated destructor stub
}

//returns whose Army is positioned at coords
int GameLogic::whoseArmy(coordinates coords) {
	int playerId=0;

	std::cout << "\nCoord.x="<<coords.x << " Coord.y=" << coords.y << "\n";


	 for (std::list<Player*>::iterator pl = playerlist->begin(); pl != playerlist->end(); pl++){

		 Player *p=*pl;



		 for(std::list<EArmy>::iterator ar=p->armies.begin();ar!=p->armies.end();ar++ ){
			 coordinates pos=ar->getCoords();

			 if(pos.x==coords.x && pos.y==coords.y){
				 playerId=p->getPlayerId();
			 }
			 pos.~coordinates();
		 }

	 }

	return playerId;
}

//return whose Place is at coords
int GameLogic::whosePlace(coordinates coords) {
	int playerId;

	for(std::list<Player*>::iterator pl=playerlist->begin();pl!=playerlist->end();pl++){
		Player* p=*pl;

		for(std::list<EPlace>::iterator pla=p->places.begin();pla!=p->places.end();pla++){
			coordinates pos=pla->getCoords();
			if(pos.x==coords.x && pos.y==coords.y){
				playerId=p->getPlayerId();
			}
		}
	}

	return playerId;
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

		bool b=map->isArmyPositioned(where);

		int playerId=whoseArmy(where);

		if(b==0){
			valid=(player->getPlayerId()!=whoseArmy(where))?true:false;
		}


	}

	return valid;
}

