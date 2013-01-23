/*
 * GameEngine.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */
#include <iostream>

#include <boost/bind.hpp>

#include <gamemodel/Player.h>
#include <gamemodel/GameAction.h>
#include <gamemodel/entities/ELocation.h>

#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ABuild.h>
#include <gamemodel/actions/AAttack.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>
#include <gamemodel/actions/ALogIn.h>

#include <gamemodel/ressources/RMoney.h>

#include <network/messages/statemessages/SMUpdateRessources.h>
#include <network/messages/statemessages/SMUpdateUUID.h>
#include <network/messages/statemessages/SMSetStartBase.h>
#include <network/messages/statemessages/SMUpdateActionsLeft.h>
#include <network/messages/statemessages/SMBattleResult.h>

#include <network/ServerNetwork.h>

#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine(GameMapServer *map, GameContainer *container) :
		map(map), container(container), isRunning(true), logic(map, container), m_network(
				1337) {
}

GameEngine::~GameEngine() {
}

bool GameEngine::onPlayerConnect(PlayerPtr player) {
	container->addPlayer(player);
	return true;
}

void GameEngine::onPlayerDisconnect(PlayerPtr player) {
}

void GameEngine::onPlayerAction(GameActionPtr action, PlayerPtr player) {
	if (logic.checkPlayerAction(player, action) == true) {
		doAction(player, action);
	} else {
	}
}

void GameEngine::doAction(PlayerPtr player, GameActionPtr action) {
	ARecruitPtr recruit = boost::dynamic_pointer_cast<ARecruit>(action);
	ASetAPPtr setAP = boost::dynamic_pointer_cast<ASetAP>(action);
	ASetTurnPtr setTurn = boost::dynamic_pointer_cast<ASetTurn>(action);

	AMovePtr move = boost::dynamic_pointer_cast<AMove>(action);
	ABuildPtr build = boost::dynamic_pointer_cast<ABuild>(action);
	AAttackPtr attack = boost::dynamic_pointer_cast<AAttack>(action);

	ALogInPtr logIn = boost::dynamic_pointer_cast<ALogIn>(action);

	if (recruit != NULL) {
		BroadcastAction(onPlayerRecruit(player, recruit));
		SendUpdateRessources(player);
	}
	if (setAP != NULL) {
		BroadcastAction(onPlayerSetAP(player, setAP));
	}
	if (setTurn != NULL) {
		onPlayerSetTurn(player, setTurn);
	}
	if (move != NULL) {
		onPlayerMove(player, move);
	}
	if (build != NULL) {
		BroadcastAction(onPlayerBuild(player, build));
	}
	if (attack != NULL) {
		onPlayerAttack(player, attack);
	}
	if (logIn != NULL) {
		onPlayerLogIn(player, logIn);
	}



	if(recruit != NULL or move != NULL or build != NULL or attack != NULL){
		player->SetActionLeft(player->GetActionLeft() - 1);
		SendUpdateActionsLeft(player);
	}

	std::cout << "\n---------------------------------------------------------------\n";
}
void GameEngine::onPlayerLogIn(PlayerPtr player, ALogInPtr logIn) {
	//we need the same ID
	SendUpdateUUID(player);

	onPlayerConnect(player);

	logIn->verified = true;

	GameActionPtr ret(logIn);
	m_network.SendAction(player, ret);

	if (container->getPlayerCount() > 1) {
		if ((rand() % 2) == 0) {
			ASetTurnPtr setturn2(new ASetTurn);

			setturn2->endturn = false;
			m_network.SendAction(player, setturn2);

			setturn2->endturn = true;
			for (auto players : *(container->getPlayerListPtr())) {
				if (players->getPlayerIdStr() != player->getPlayerIdStr()) {
					m_network.SendAction(players, setturn2);
					//dies funktioniert nur für 2 spieler!
					break;
				}
			}

		} else {

			ASetTurnPtr setturn2(new ASetTurn);
			setturn2->endturn = true;
			m_network.SendAction(player, setturn2);
			setturn2->endturn = false;
			for (auto players : *(container->getPlayerListPtr())) {
				if (players->getPlayerIdStr() != player->getPlayerIdStr()) {
					m_network.SendAction(players, setturn2);
					//dies funktioniert nur für 2 spieler!
					break;
				}
			}
		}
	}
	if (container->getPlayerCount() == 2) {
		startSession();
	}
}

void GameEngine::SendSetStartbase(PlayerPtr player, coordinates coords) {

	SMSetStartBasePtr setstartbase(new SMSetStartBase);

	setstartbase->coords.x = coords.x;
	setstartbase->coords.y = coords.y;

	GameStateMessagePtr message(setstartbase);
	m_network.SendMessageA(player, message);

}

void GameEngine::SendUpdateUUID(PlayerPtr player) {

	SMUpdateUUIDPtr update_id(new SMUpdateUUID);

	update_id->id = player->getPlayerId();

	GameStateMessagePtr message(update_id);
	m_network.SendMessageA(player, message);
}

void GameEngine::SendBattleResult(PlayerPtr player, EArmyPtr army, coordinates coords){
	SMBattleResultPtr battle_result(new SMBattleResult);
	battle_result->winner=army;
	battle_result->looser_cords.x = coords.x;
	battle_result->looser_cords.y = coords.y;

	GameStateMessagePtr message(battle_result);
	m_network.SendMessageA(player,message);
}

void GameEngine::SendUpdateActionsLeft(PlayerPtr player){
	SMUpdateActionsLeftPtr update_action_left(new SMUpdateActionsLeft);
	update_action_left->actions_left =player->GetActionLeft();
	GameStateMessagePtr message(update_action_left);
	m_network.SendMessageA(player,message);
}

void GameEngine::SendUpdateRessources(PlayerPtr player) {
	SMUpdateRessourcesPtr updateres(new SMUpdateRessources);
	updateres->gold = player->getGold();//test

	updateres->wood = player->getWood();
	updateres->stone = player->getStone();
	GameStateMessagePtr message(updateres);
	m_network.SendMessageA(player, message);
}

void GameEngine::onNextTurn() {
	//reset StepsLeft
	for (auto player : *(container->getPlayerListPtr())) {
		player->SetActionLeft(10);
		for (auto army : *(container->getArmyListPtr())) {
			army->SetStepsLeft(2);
		}
	}
}

void GameEngine::createArmyAt(coordinates coords, PlayerPtr owner) {
	map->setArmy(coords);
	EArmyPtr army(new EArmy);
	army->setCoords(coords);
	army->SetStepsLeft(2);
	army->SetOwner(owner->getPlayerId());

	container->addArmy(army);
}

GameActionPtr GameEngine::onPlayerRecruit(PlayerPtr player,
		ARecruitPtr recruit) {

	player->setGold(player->getGold() - recruit->what->cost_gold);
	player->setWood(player->getWood() - recruit->what->cost_wood);
	player->setStone(player->getStone() - recruit->what->cost_stone);

	EUnitPtr unit(recruit->what);
	ELocationPtr base(map->getLocationAt(recruit->base->getCoords()));
	GameRessourcePtr costs(recruit->costs);

	if (recruit->inside == true) {
		base->town_army->AddUnit(unit);
		unit->SetOwner(player->getPlayerId());
	} else {
		if (map->isArmyPositioned(base->GetAssemblyPointCoords()) == false) {
			createArmyAt(base->GetAssemblyPointCoords(), player);
		}

//the new army object
		EArmyPtr armyat(container->getArmyAt(base->GetAssemblyPointCoords()));
		armyat->SetOwner(player->getPlayerId());

//set coords of unit
		unit->setCoords(base->GetAssemblyPointCoords());
		unit->SetOwner(player->getPlayerId());
//unit added to player and army
		player->addUnit(unit);
		armyat->AddUnit(unit);

	}

	recruit->base = base;

	ARecruitPtr action(recruit);
	return action;
}

void GameEngine::onPlayerMove(PlayerPtr player, AMovePtr move) {
	GameEntityPtr what(move->what);

	coordinates from = what->getCoords();
	coordinates to = move->to;
	int size = move->count;
	EArmyPtr army(container->getArmyAt(from));

	if (army->GetOwner() == player->getPlayerId()) {
		if ((army->GetStepsLeft() - size) >= 0) {
			if (map->isBlocked(to) == false) {
				if (map->isWalkable(to) == true and map->isPlace(to) == false
						and map->isArmyPositioned(to) == false) {
					map->setWalkable(from);
					army->setCoords(to);
					map->setArmy(to);
				} else if (map->isPlace(to) == true) {
//merge into place
				} else if (map->isArmyPositioned(to) == true) {
//merge into army
				}
				army->SetStepsLeft(army->GetStepsLeft() - size);
			}
		}
		AMovePtr action(move);
		BroadcastAction(action);
	}

}

GameActionPtr GameEngine::onPlayerBuild(PlayerPtr player, ABuildPtr build) {
	EBuildingPtr building(build->what);
	ELocationPtr where(build->where);
	where->addBuilding(building);

	ABuildPtr action(build);
	return action;
}

void GameEngine::onPlayerAttack(PlayerPtr player, AAttackPtr attack) {
	coordinates where = attack->target;

	EArmyPtr attacker_army(map->getArmyAt(attack->attacker));
	EArmyPtr enemyarmy(map->getArmyAt(attack->target));

	PlayerPtr enemyplayer(container->getPlayerById(map->whoseArmyAt(attack->target)));

	if (attacker_army->units.size() > enemyarmy->units.size()) {
		map->setWalkable(where);
		enemyplayer->armies.remove(enemyarmy);
		attacker_army->SetOwner(player->getPlayerId());
		SendBattleResult(player, attacker_army, where);
		SendBattleResult(enemyplayer, attacker_army, where);
	} else {
		map->setWalkable(attack->attacker);
		player->armies.remove(attacker_army);
		enemyarmy->SetOwner(enemyplayer->getPlayerId());
		SendBattleResult(player, enemyarmy, attack->attacker);
		SendBattleResult(enemyplayer, enemyarmy, attack->attacker);
	}
}

GameActionPtr GameEngine::onPlayerSetAP(PlayerPtr player, ASetAPPtr setAP) {
	ELocationPtr place(map->getLocationAt(setAP->basecoords));
	place->SetAssemblyPointCoords(setAP->apcoords);

	ASetAPPtr action(setAP);
	return action;
}

void GameEngine::onPlayerSetTurn(PlayerPtr player, ASetTurnPtr setTurn) {

	if (setTurn->endturn == true) {
		//player end the turn
		player->onturn = false;
		ASetTurnPtr setturn2(new ASetTurn);

		setturn2->endturn = true;
		m_network.SendAction(player, setturn2);

		if (container->getPlayerCount() > 1) {
			setturn2->endturn = false;
			for (int i = 0; i < container->getPlayerCount(); i++) {
				if (container->getPlayer(i)->getPlayerId()
						!= player->getPlayerId()) {
					m_network.SendAction(container->getPlayer(i), setturn2);
				}
			}
		}
	} else {
		//player start turn
		player->onturn = true;
		ASetTurnPtr setturn2(new ASetTurn);
		setturn2->endturn = false;
		m_network.SendAction(player, setturn2);

		if (container->getPlayerCount() > 1) {
			setturn2->endturn = true;
			for (auto players : *(container->getPlayerListPtr())) {
				if (players->getPlayerId() != player->getPlayerId()) {
					m_network.SendAction(players, setturn2);
					break;
				}
			}
		}
	}
	onNextTurn();
}

void GameEngine::BroadcastAction(GameActionPtr action) {
	for (auto player : *(container->getPlayerListPtr())) {
		m_network.SendAction(player, action);
	}
}

void GameEngine::startSession() {
	int counter = 1;

	//for (auto location : *(container->getLocationListPtr())) {
	for (auto location :map->placeList) {

		if (map->isStartBase(location->getCoords())) {
			int i = 1;
			for (auto player : *(container->getPlayerListPtr())) {
				if (counter == i) {
					player->addLocation(location);
					//das kann auch in playerfkt addLocation
					location->owned = true;
					location->SetOwner(player->getPlayerId());
					SendSetStartbase(player,location->getCoords());
					//--------------------------------------
				}
				counter++;
			}
			counter = 0;
		}
	}
}

void GameEngine::attackArmy(EArmyPtr attacker, EArmyPtr defender) {

}

void GameEngine::run() {
	m_network.ConnectOnAction(boost::bind(&GameEngine::onPlayerAction, this, _1, _2));
	m_network.thread()->join();
}
