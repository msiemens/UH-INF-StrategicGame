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

#include <gamemodel/ressources/RMoney.h>

#include <network/ServerNetwork.h>

#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine(GameMap *map, list<PlayerPtr> *playerlist) :
		map(map),
		playerlist(playerlist),
		isRunning(true),
		logic(map, playerlist),
		m_network(1337) {
	//test();
}

GameEngine::~GameEngine() {
}

bool GameEngine::onPlayerConnect(PlayerPtr player) {
	//std::cout << "\nSpieler mit ID "<< player->getPlayerId() << " hat sich connected";
	playerlist->insert(playerlist->end(), player);
	return true;
}

void GameEngine::onPlayerDisconnect(PlayerPtr player) {
}

void GameEngine::onPlayerAction(GameActionPtr action, PlayerPtr player) {
	cout << "GameEngine::onPlayerAction(...)" << endl;
	if (logic.checkPlayerAction(player, action) == true) {
		std::cout << "Action ist gueltig.\n";
		doAction(player, action);
		std::cout << "Action ausgeführt.\n";
	} else {
		std::cout << "Action von Spieler #" << player->getPlayerIdStr()
				<< " ist ungueltig.\n";
	}
}

void GameEngine::doAction(PlayerPtr player, GameActionPtr action) {
	std::cout << "GameEngine::doAction(...).\n";

	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	ASetAP* setAP = dynamic_cast<ASetAP*>(action.get());
	ASetTurn* setTurn = dynamic_cast<ASetTurn*>(action.get());

//	AMove* move = dynamic_cast<AMove*>(action.get());
//	ABuild* build = dynamic_cast<ABuild*>(action.get());
//	AAttack* attack = dynamic_cast<AAttack*>(action.get());

	std::cout << "GameEngine::doAction: checking type.\n";
	if (recruit != NULL) {
		std::cout << "GameEngine::doAction: got a ARecruit.\n";
		if(recruit->inside == true){

			EUnitPtr unit(recruit->what);
			ELocationPtr base(map->getPlaceAt(recruit->base->getCoords()));
			GameRessourcePtr costs(recruit->costs);
			bool inside(recruit->inside);

			base->town_army->AddUnit(unit);

			//prepare gameaction
			ARecruitPtr action2(new ARecruit);
			action2->what = unit;
			action2->base = base;
			action2->inside = recruit->inside;
			m_network.SendAction(player,action2);
			std::cout << "GameEngine::doAction: successful.\n";

			//player->addUnit(unit);
		}else{
			m_network.BroadcastAction(action);
			std::cout << "GameEngine::doAction: successful.\n";
		}
	}
	if(setAP != NULL){
		ASetAPPtr setAP2(new ASetAP);
		setAP2->apcoords.x = setAP->apcoords.x;
		setAP2->apcoords.y = setAP->apcoords.y;
		setAP2->basecoords.x = setAP->basecoords.x;
		setAP2->basecoords.y = setAP->basecoords.y;
		m_network.SendAction(player,setAP2);
	}

	if(setTurn != NULL){
		if(setTurn->endturn == true){
			player->onturn = false;
			ASetTurnPtr setturn2(new ASetTurn);
			setturn2->endturn = true;
			m_network.SendAction(player,setturn2);

			setturn2->endturn = false;
			for(auto players : *playerlist){
				if(players->getPlayerIdStr() != player->getPlayerIdStr()){
					//dies funktioniert nur für 2 spieler!
					m_network.SendAction(players,setturn2);
					break;
				}
			}
		}else{
			player->onturn = true;
			ASetTurnPtr setturn2(new ASetTurn);
			setturn2->endturn = false;
			m_network.SendAction(player,setturn2);

			setturn2->endturn = true;
			for(auto players : *playerlist){
				if(players->getPlayerIdStr() != player->getPlayerIdStr()){
					//dies funktioniert nur für 2 spieler!
					m_network.SendAction(players,setturn2);
					break;
				}
			}
		}
	}


//	if (move != NULL) {
//		std::cout << "GameEngine::doAction: got a AMove.\n";
//		map->printMapStatus();
//		GameEntityPtr what(move->what);
//
//		coordinates from = what->getCoords();
//		coordinates to = move->to;
//
//		map->setArmy(to);
//		map->setWalkable(from);
//
//		what->setCoords(to);
//
//		map->printMapStatus();
//
//	}
//	if (build != NULL) {
//		std::cout << "GameEngine::doAction: got a ABuild.\n";
//		EBuildingPtr building(build->what);
//		ELocationPtr where(build->where);
//		where->addBuilding(building);
//	}
//	if (attack != NULL) {
//		std::cout << "GameEngine::doAction: got a AAttack.\n";
//		GameEntityPtr what(attack->what);
//		coordinates where = attack->where;
//
//		EArmyPtr enemyarmy;
//		PlayerPtr enemyplayer;
//
//		for (auto p : *playerlist) {
//			for (auto army : p->armies) {
//				if (army->getCoords().x == where.x
//						&& army->getCoords().y == where.y) {
//					EArmyPtr ea(army);
//					PlayerPtr ep(p);
//
//					enemyarmy = ea;
//					enemyplayer = ep;
//				}
//			}
//		}
//	}

	//m_network.SendAction(player,action);
	//GameNetwork.broadcast(action);

}

void GameEngine::run() {
	m_network.ConnectOnAction(
			boost::bind(&GameEngine::onPlayerAction, this, _1, _2));
	m_network.thread()->join();
}
