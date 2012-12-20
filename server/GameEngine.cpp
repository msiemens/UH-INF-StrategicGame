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

#include <gamemodel/ressources/RMoney.h>

#include <network/ServerNetwork.h>

#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine(GameMap *map, list<PlayerPtr> *playerlist) :
		map(map),
		playerlist(playerlist),
		isRunning(true),
		logic(map, playerlist),
		m_network(1337),
		player(new Player) {
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

void GameEngine::onPlayerAction(/* PlayerPtr player, */GameActionPtr action) {
	cout << "GameEngine::onPlayerAction(...)" << endl;
	if (logic.checkPlayerAction(player, action) == true) {
		std::cout << "Action ist gueltig.\n";
		doAction(player, action);
	} else {
		std::cout << "Action von Spieler #" << player->getPlayerIdStr()
				<< " ist ungueltig.\n";
	}
}

void GameEngine::doAction(PlayerPtr player, GameActionPtr action) {
	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	AMove* move = dynamic_cast<AMove*>(action.get());
	ABuild* build = dynamic_cast<ABuild*>(action.get());
	AAttack* attack = dynamic_cast<AAttack*>(action.get());

	if (recruit != NULL) {

		EUnitPtr unit(recruit->what);
		// ELocationPtr base(recruit->base);
		GameRessourcePtr costs(recruit->costs);

		player->addUnit(unit);

	}
	if (move != NULL) {

		map->printMapStatus();
		GameEntityPtr what(move->what);

		coordinates from = what->getCoords();
		coordinates to = move->to;

		map->setArmy(to);
		map->setWalkable(from);

		what->setCoords(to);

		map->printMapStatus();

	}
	if (build != NULL) {
		EBuildingPtr building(build->what);
		ELocationPtr where(build->where);
		where->addBuilding(building);
	}
	if (attack != NULL) {
		GameEntityPtr what(attack->what);
		coordinates where = attack->where;

		EArmyPtr enemyarmy;
		PlayerPtr enemyplayer;

		for (auto p : *playerlist) {
			for (auto army : p->armies) {
				if (army->getCoords().x == where.x
						&& army->getCoords().y == where.y) {
					EArmyPtr ea(army);
					PlayerPtr ep(p);

					enemyarmy = ea;
					enemyplayer = ep;
				}
			}
		}
	}

	//GameNetwork.broadcast(action);

}

void GameEngine::run() {
	m_network.ConnectOnAction(
			boost::bind(&GameEngine::onPlayerAction, this, _1));
	m_network.thread()->join();
}
