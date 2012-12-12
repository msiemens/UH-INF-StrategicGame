/*
 * GameEngine.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */
#include <iostream>

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

#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine(GameMap *map) :
		map(map), isRunning(true),logic(map,&playerlist) {
	std::cout << "\nEngine started";
	test();
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

bool GameEngine::onPlayerConnect(Player player) {
	std::cout << "\nMethodenaufruf: onPlayerConnect() von";
	playerlist.insert(playerlist.begin(), player);
	return true;
}

void GameEngine::onPlayerDisconnect(Player player) {
	// playerlist.remove(&player);
}

void GameEngine::onPlayerAction(Player player, GameAction *action) {
	std::cout << "\nMethodenaufruf onPlayerAction()";
	if (logic.checkPlayerAction(player, action) == true) {
		doAction(player, action);
	}

}

void GameEngine::doAction(Player player, GameAction *action) {

	ARecruit* recruit = dynamic_cast<ARecruit*>(action);
	AMove* move = dynamic_cast<AMove*>(action);
	ABuild* build = dynamic_cast<ABuild*>(action);
	AAttack* attack = dynamic_cast<AAttack*>(action);


	if (recruit != NULL) {

		ETroops troops = recruit->what;
		EPlace base = recruit->base;

		player.addTroops(troops);
		base.positionedarmy.addTroop(troops, 0);

		std::cout << "\nEngine führt Recruit-Befehl aus. \n";

	}
	if (move != NULL) {
		GameEntity what=move->what;
		//EArmy* army=dynamic_cast<EArmy*>(&what);
		coordinates coords=move->to;

		map->setArmy(coords);
		map->isWalkable(coords);

		//army->setPosition(coords);

		std::cout << "\nEngine führt Move-Befehl aus.\n";
	}
	if (build != NULL) {
		EBuilding building = build->what;
		EPlace where = build->where;
		where.addBuilding(building);
		std::cout << "\nEngine führt Build-Befehl aus.\n";
	}
	if (attack != NULL) {
		std::cout << "\nEngine führt Attack-Befehl aus.\n";
	}

	//GameNetwork.broadcast(action);

}

void GameEngine::test() {

	std::cout << "\nTest started\n\n\n";
	Player player1(0);
	Player player2(1);
	onPlayerConnect(player1);
	std::cout << " player1\n";
	onPlayerConnect(player2);
	std::cout << " player2\n";

	EMetropolis rome;
	EMetropolis athens;

	rome.coords = coordinates(0, 0);
	athens.coords = coordinates(3, 3);
	rome.inhabitans = 100;
	athens.inhabitans = 100;

	player1.addPlace(rome);
	player2.addPlace(athens);

	map->setPlace(rome.coords);
	map->setPlace(athens.coords);

	//P1 baut Kaserne in place rome
	std::cout << "\nBuild Befehl von player1";
	ABuild buildcinrome;
	buildcinrome.where = rome;

	ECasern casernir;
	buildcinrome.what = casernir;

	RMoney money;
	buildcinrome.costs=money;

	onPlayerAction(player1, &buildcinrome);

	//P2 baut Kaserne in place athens
	std::cout << "\nBuild Befehl von player2";
	ABuild buildcinathens;
	buildcinathens.where = athens;

	ECasern casernia;
	buildcinathens.what = casernia;

	buildcinathens.costs=money;

	onPlayerAction(player2, &buildcinathens);

	//P1 rekrutiert Infantrie in place rome
	std::cout << "\nRecruit-Befehl von player1";
	ARecruit recruiti;
	recruiti.base = rome;

	EInfantry infantry;
	recruiti.what = infantry;

	recruiti.costs = money;

	onPlayerAction(player1, &recruiti);

	//P2 rekrutiert Bauern in place athens
	std::cout << "Recruit-Befehl von player2";
	ARecruit recruitp;
	recruitp.base = athens;

	EPawn pawn;
	recruitp.what = pawn;

	recruitp.costs = money;

	onPlayerAction(player2, &recruitp);

	//armies werden erstellt und zugewiesen

	EArmy army1;
	player1.addArmy(army1);

	EArmy army2;
	player2.addArmy(army2);

	army1.addTroop(infantry, 0);
	army2.addTroop(pawn, 0);

	army1.setPosition(rome.coords);
	army2.setPosition(athens.coords);

	//army1 wird bewegt
	std::cout << "\nMove-Befehl von player1";
	AMove move1;
	move1.what = army1;
	move1.to = coordinates(2, 2);

	onPlayerAction(player1, &move1);

	//army2 wird bewegt
	std::cout << "\nMove-Befehl von player2";
	AMove move2;
	move2.what = army2;
	move2.to = coordinates(0, 3);

	onPlayerAction(player2, &move2);

	onPlayerDisconnect(player1);
	onPlayerDisconnect(player2);

	std::cout << "\n\n\nTest ended";

}



