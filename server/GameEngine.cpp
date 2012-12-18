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
#include <gamemodel/entities/EPlace.h>

#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ABuild.h>
#include <gamemodel/actions/AAttack.h>

#include <gamemodel/entities/units/EInfantry.h>
#include <gamemodel/entities/units/EPawn.h>
#include <gamemodel/entities/buildings/ECasern.h>
#include <gamemodel/entities/places/EMetropolis.h>

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

		ETroopsPtr troops(recruit->what);
		// EPlacePtr base(recruit->base);
		GameRessourcePtr costs(recruit->costs);

		player->addTroops(troops);

		std::cout << "Spieler #" << player->getPlayerIdStr() << " rekrutiert "
				<< troops->getName() /* << " in " << base->getName() */
				<< ".\n";

	}
	if (move != NULL) {

		map->printMapStatus();
		GameEntityPtr what(move->what);

		coordinates from = what->getCoords();
		coordinates to = move->to;

		map->setArmy(to);
		map->setWalkable(from);

		what->setCoords(to);

		std::cout << "Spieler #" << player->getPlayerIdStr() << " bewegt "
				<< what->getName() << " nach " << to.x << "/" << to.y << ".\n";

		map->printMapStatus();

	}
	if (build != NULL) {
		EBuildingPtr building(build->what);
		EPlacePtr where(build->where);
		where->addBuilding(building);

		std::cout << "Spieler #" << player->getPlayerIdStr() << " baut "
				<< building->getName() << " in " << where->getName() << ".\n";
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

		std::cout << "Spieler #" <<player->getPlayerIdStr()<<" greift mit "
				<< what->getName() << ", " << enemyarmy->getName() << ""
						" von Spieler #"
				<< enemyplayer->getPlayerIdStr() <<" an.\n";

	}

	//GameNetwork.broadcast(action);

}

void GameEngine::run() {
	m_network.ConnectOnAction(
			boost::bind(&GameEngine::onPlayerAction, this, _1));
	m_network.thread()->join();
	//test
}

void GameEngine::test() {

	std::cout << "Server wurde gestartet.\nTest wurde gestartet.\n";

	std::cout << "------------------------------\n";

	onPlayerConnect(player);

	std::cout << "------------------------------\n";

	EPlacePtr rome(new EMetropolis);
	EPlacePtr athens(new EMetropolis);

	rome->setName("Rom");
	athens->setName("Athen");

	player->addPlace(rome);
	player->addPlace(athens);

	std::cout << "------------------------------\n";

	EArmyPtr army1(new EArmy);
	EArmyPtr army2(new EArmy);

	army1->setName("Armee Spieler 1");
	army2->setName("Armee Spieler 2");

	player->addArmy(army1);
	player->addArmy(army2);

	army1->setCoords(coordinates(0, 0));
	army2->setCoords(coordinates(3, 3));

	map->setArmy(coordinates(0, 0));
	map->setArmy(coordinates(3, 3));

	std::cout << "------------------------------\n";

	ABuildPtr buildcr(new ABuild);
	EBuildingPtr casernr(new ECasern);

	buildcr->what = casernr;
	buildcr->where = rome;
	onPlayerAction(buildcr);

	std::cout << "------------------------------\n";

	ABuildPtr buildca(new ABuild);
	EBuildingPtr caserna(new ECasern);

	buildca->what = caserna;
	buildca->where = athens;
	onPlayerAction(buildca);

	std::cout << "------------------------------\n";

	ARecruitPtr recruiti(new ARecruit);
	ETroopsPtr infantry(new EInfantry);
	EPlacePtr baser(rome);

	recruiti->what = infantry;
	recruiti->base = baser;

	onPlayerAction(recruiti);

	std::cout << "------------------------------\n";

	ARecruitPtr recruitp(new ARecruit);
	ETroopsPtr pawn(new EPawn);
	EPlacePtr basea(athens);

	recruitp->what = pawn;
	recruitp->base = basea;

	onPlayerAction(recruitp);

	std::cout << "------------------------------\n";

	AMovePtr move1(new AMove);

	move1->what = army1;
	move1->to = coordinates(1, 1);
	onPlayerAction(move1);

	std::cout << "------------------------------\n";

	AMovePtr move2(new AMove);

	move2->what = army2;
	move2->to = coordinates(1, 1);
	onPlayerAction(move2);

	std::cout << "------------------------------\n";

	AAttackPtr attack12(new AAttack);

	attack12->what = army1;
	attack12->where = coordinates(3, 3);

	onPlayerAction(attack12);

	std::cout << "------------------------------\n";

	onPlayerDisconnect(player);

}

