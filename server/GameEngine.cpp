/*
 * GameEngine.cpp
 *
 *  Created on: 16.11.2012
 *      Author: Armend
 */
#include <iostream>

#include "server/GameEngine.h"
#include "gamemodel/Player.h"
#include "gamemodel/GameAction.h"
#include "gamemodel/entities/EPlace.h"

#include "gamemodel/actions/ARecruit.h"
#include "gamemodel/actions/AMove.h"
#include "gamemodel/actions/ABuild.h"
#include "gamemodel/actions/AAttack.h"

#include "gamemodel/entities/units/EInfantry.h"
#include "gamemodel/entities/units/EPawn.h"
#include "gamemodel/entities/buildings/ECasern.h"
#include "gamemodel/entities/places/EMetropolis.h"

#include "gamemodel/ressources/RWood.h"

using namespace std;

GameEngine::GameEngine(GameMap map):map(map),isRunning(true){
	std::cout << "Engine started";
	logic(map,playerlist);
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

bool GameEngine::onPlayerConnect(Player player) {
	playerlist.insert(playerlist.begin(), player);
	return true;
}

void GameEngine::onPlayerDisconnect(Player player) {
	// playerlist.remove(&player);
}

void GameEngine::onPlayerAction(Player player, GameAction action) {

	if (logic.checkPlayerAction(player, action) == true) {
		doAction(player, action);
	}

}

void GameEngine::doAction(Player player, GameAction action) {
	ARecruit* recruit = dynamic_cast<ARecruit*>(&action);
	AMove* move = dynamic_cast<AMove*>(&action);
	ABuild* build = dynamic_cast<ABuild*>(&action);
	AAttack* attack = dynamic_cast<AAttack*>(&action);

	if (recruit != 0) {


		ARecruit recruit;
		ETroops troops = recruit.what;
		EPlace base = recruit.base;

		player.addTroops(troops);
		base.positionedarmy.addTroop(troops, 0);

		std::cout << "Recruit";

	}
	if (move != 0) {
		EArmy* army = dynamic_cast<EArmy*>(&move->what);
		army->setPosition(move->to);
		// map.setArmy(move->to); // TODO: Fix this when uncommented
		std::cout << "Move";
	}
	if (build != 0) {
		GameEntity building = build->what;
		EPlace where = build->where;
		//where.addBuilding(building);
		std::cout << "Build";
	}
	if (attack != 0) {
		std::cout << "Attack";
	}

	//GameNetwork.broadcast(action);

}

void GameEngine::test() {

	std::cout <<"Test started";
	Player henrik(0);
	Player armend(1);
	onPlayerConnect(henrik);
	onPlayerConnect(armend);

	EMetropolis rome;
	EMetropolis athens;

	rome.coords = coordinates(0, 0);
	athens.coords = coordinates(3, 3);
	rome.inhabitans = 100;
	athens.inhabitans = 100;

	henrik.addPlace(rome);
	armend.addPlace(athens);

	map.setPlace(rome.coords);
	map.setPlace(athens.coords);

	//H baut Kaserne in place rome

	ABuild buildcinrome;
	buildcinrome.where = rome;

	ECasern casernir;
	buildcinrome.what = casernir;

	onPlayerAction(henrik, buildcinrome);

	//A baut Kaserne in place athens

	ABuild buildcinathens;
	buildcinathens.where = athens;

	ECasern casernia;
	buildcinathens.what = casernia;
	onPlayerAction(armend, buildcinathens);

	//H rekrutiert Infantrie in place rome

	ARecruit recruiti;
	recruiti.base = rome;

	EInfantry infantry;
	recruiti.what = infantry;
	RWood wood;
	recruiti.costs = wood;

	onPlayerAction(henrik, recruiti);

	//A rekrutiert Bauern in place athens

	ARecruit recruitp;
	recruitp.base = athens;

	EPawn pawn;
	recruitp.what = pawn;

	recruitp.costs = wood;

	onPlayerAction(armend, recruitp);

	//armies werden erstellt und zugewiesen

	EArmy harmy;
	henrik.addArmy(harmy);

	EArmy aarmy;
	armend.addArmy(aarmy);

	harmy.addTroop(infantry, 0);
	aarmy.addTroop(pawn, 0);

	harmy.setPosition(rome.coords);
	aarmy.setPosition(athens.coords);

	//harmy wird bewegt

	AMove moveh;
	moveh.what = harmy;
	moveh.to = coordinates(2, 2);

	onPlayerAction(henrik, moveh);

	//aarmy wird bewegt

	AMove movea;
	movea.what = aarmy;
	movea.to = coordinates(0, 3);

	onPlayerAction(armend, movea);

	onPlayerDisconnect(armend);
	onPlayerDisconnect(henrik);

}

