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
#include <gamemodel/GameMap.h>
#include <gamemodel/Player.h>
#include <gamemodel/GameAction.h>
#include <gamemodel/entities/EArmy.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/ABuild.h>
#include <gamemodel/actions/AAttack.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>
#include <gamemodel/actions/ALogIn.h>

#include <gamemodel/ressources/RMoney.h>

GameLogic::GameLogic(GameMapServer *map, GameContainer *container) :
		map(map), container(container) {
}

GameLogic::~GameLogic() {
}

//checks whether PlacerAction is valid or not
bool GameLogic::checkPlayerAction(PlayerPtr player, GameActionPtr action) {
	bool valid = false;

	ARecruitPtr recruit = boost::dynamic_pointer_cast<ARecruit>(action);
	ASetAPPtr setAP = boost::dynamic_pointer_cast<ASetAP>(action);
	ASetTurnPtr setTurn = boost::dynamic_pointer_cast<ASetTurn>(action);

	AMovePtr move = boost::dynamic_pointer_cast<AMove>(action);
	ABuildPtr build = boost::dynamic_pointer_cast<ABuild>(action);
	AAttackPtr attack = boost::dynamic_pointer_cast<AAttack>(action);

	ALogInPtr logIn = boost::dynamic_pointer_cast<ALogIn>(action);

//recruit
	if (recruit != NULL) {
		if (player->GetActionLeft() > 0) {
			GameRessourcePtr costs(recruit->costs);
			EUnitPtr troops(recruit->what);
			ELocationPtr base(recruit->base);

			if (player->getGold() >= recruit->what->cost_gold
					and player->getWood() >= recruit->what->cost_wood
					and player->getStone() >= recruit->what->cost_stone) {

				if (recruit->inside) {
					if (base->town_army->units.size() < 10
							and map->whosePlace(base->getCoords())
									== player->getPlayerId()) {
						valid = true;
					} else {
						valid = false;
					}
				} else { //outside
					if (map->whosePlace(base->getCoords())
							== player->getPlayerId()) {
						if (map->isArmyPositioned(
								base->GetAssemblyPointCoords())
								and container->getArmyAt(base->GetAssemblyPointCoords())->units.size()
										< 10
								and container->getArmyAt(base->GetAssemblyPointCoords())->GetOwner()
										== player->getPlayerId()) {
							valid = true;

						} else if (map->isWalkable(
								base->GetAssemblyPointCoords())) {
							valid = true;
						}
					}
				}
			} else { //check ressources
				valid = false;
			}
		} //actionsleft
	}

//move
	else if (move != NULL) {
		std::cout << "Logic move" << endl;
		GameEntityPtr what(move->what);
		coordinates from=what->getCoords();
		coordinates to = move->to;

		valid = (map->isWalkable(to) or (map->isArmyPositioned(to) and map->whoseArmyAt(to)==player->getPlayerId()
		and container->getArmyAt(to)->units.size()+container->getArmyAt(from)->units.size() < 12) or (map->isPlace(to) and
				map->whoseLocationAt(to)==player->getPlayerId() and map->getLocationAt(to)->town_army->units.size()<12)) ? true : false;
	}
//build
	else if (build != NULL) {
		if(player->GetActionLeft() > 0){
			GameRessourcePtr costs(build->costs);
			EBuildingPtr building(build->what);
			ELocationPtr where(build->where);

			valid = true;
		}
	}
//setAP
	else if (setAP != NULL) {
		std::cout << "logic setap" << endl;
		coordinates apcoord(setAP->apcoords);
		coordinates basecoord(setAP->basecoords);

		valid=(((apcoord.x != basecoord.x or apcoord.y != basecoord.y) and map->isBlocked(apcoord)==false and map->isArmyPositioned(apcoord) == false)

				or(map->isArmyPositioned(apcoord) == true and map->whoseArmyAt(apcoord) == player->getPlayerId()))?true:false;
	}
//setTurn
	else if (setTurn != NULL) {
		bool endturn = setTurn->endturn;
		valid = true;
	}
//attack
	else if (attack != NULL) {
		if(player->GetActionLeft() > 0){
			if (map->isArmyPositioned(attack->target)) {
				valid = (player->getPlayerId() != map->whoseArmyAt(attack->target)
						and player->getPlayerId()
								== map->whoseArmyAt(attack->attacker)) ?
						true : false;
			} else if(map->isPlace(attack->target)){
				valid=(player->getPlayerId() != map->whoseLocationAt(attack->target) and map->whoseArmyAt(attack->attacker)== player->getPlayerId())?true:false;
			}
		}
	}
//login
	else if (logIn != NULL) {
		if (container->getPlayerCount() < 1) {
			valid = true;
		} else {

			for (auto p : *(container->getPlayerListPtr())) {
				if (player->getPlayerId() == p->getPlayerId()) {
					valid = false;
				} else {
					valid = true;
				}
			}
		}
	}

	return valid;
}

