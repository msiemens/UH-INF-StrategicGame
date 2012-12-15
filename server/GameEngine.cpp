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

GameEngine::GameEngine(GameMap *map,list<Player> *playerlist) :
		map(map), playerlist(playerlist),isRunning(true),logic(map,playerlist) {
	test();
}

GameEngine::~GameEngine() {
	// TODO Auto-generated destructor stub
}

bool GameEngine::onPlayerConnect(Player player) {
	std::cout << "\nSpieler mit ID "<< player.getPlayerId() << " hat sich connected";
	playerlist->insert(playerlist->begin(), player);
	return true;
}

void GameEngine::onPlayerDisconnect(Player player) {
}

void GameEngine::onPlayerAction(Player player, GameAction *action) {
	if (logic.checkPlayerAction(&player, action) == true) {
		doAction(&player, action);
	}

}

void GameEngine::doAction(Player *player, GameAction *action) {

	ARecruit* recruit = dynamic_cast<ARecruit*>(action);
	AMove* move = dynamic_cast<AMove*>(action);
	ABuild* build = dynamic_cast<ABuild*>(action);
	AAttack* attack = dynamic_cast<AAttack*>(action);


	if (recruit != NULL) {

		ETroops troops = recruit->what;
		EPlace base = recruit->base;
		GameRessource costs=recruit->costs;

		player->addTroops(troops);
		base.positionedarmy.addTroop(troops);

		std::cout << "\nSpieler "<< player->getPlayerId() << " rekrutiert " << troops.getName() << " in " <<
				base.getName();


	}
	if (move != NULL) {
		GameEntity what=move->what;
		coordinates from=what.getCoords();

		coordinates to=move->to;

		std::cout << "\n";
		map->printMapStatus();

		map->setArmy(to);
		map->isWalkable(from);

		std::cout << "\nSpieler " <<player->getPlayerId() << " bewegt " << what.getName() << " von "
				<< from.x <<","<< from.y<< " nach " << to.x << "," << to.y;

		std::cout << "\n";
		map->printMapStatus();


	}
	if (build != NULL) {
		EBuilding building = build->what;
		EPlace where = build->where;
		where.addBuilding(building);

		std::cout << "\nSpieler "<<player->getPlayerId() << " baut " << building.getName() << " in "
				<< where.getName();

	}
	if (attack != NULL) {/*
		EArmy what=attack->what;
		coordinates where=attack->where;
		EArmy who;

		for(int i=0;i<2;i++){
			Player p=playerlist[i];
			EArmy parmy=p.armies[0];
			if(parmy.getCoords()==where){
				std::cout << "attack army";
			}
		}*/


	}

	//GameNetwork.broadcast(action);

}



void GameEngine::test() {


	//map->printMapStatus();

	Player player1(0);
	Player player2(1);
	onPlayerConnect(player1);

	onPlayerConnect(player2);


	EMetropolis rome;
	EMetropolis athens;

	rome.setName("Rom");
	athens.setName("Athen");

	rome.setCoords(coordinates(0, 0));
	athens.setCoords(coordinates(3, 3));
	rome.inhabitans = 100;
	athens.inhabitans = 100;

	player1.addPlace(rome);
	player2.addPlace(athens);

	map->setPlace(rome.getCoords());
	map->setPlace(athens.getCoords());



	//map->printMapStatus();

	//P1 baut Kaserne in place rome

	ABuild buildcinrome;
	buildcinrome.where = rome;

	ECasern casernir;
	casernir.setName("Kaserne");
	buildcinrome.what = casernir;

	RMoney money;
	buildcinrome.costs=money;

	onPlayerAction(player1, &buildcinrome);

	//P2 baut Kaserne in place athens

	ABuild buildcinathens;
	buildcinathens.where = athens;

	ECasern casernia;
	casernia.setName("Kaserne");
	buildcinathens.what = casernia;


	onPlayerAction(player2, &buildcinathens);

	//P1 rekrutiert Infantrie in place rome

	ARecruit recruiti;
	recruiti.base = rome;

	EInfantry infantry;
	infantry.setName("Infantrie");
	recruiti.what = infantry;



	onPlayerAction(player1, &recruiti);

	//P2 rekrutiert Bauern in place athens

	ARecruit recruitp;
	recruitp.base = athens;

	EPawn pawn;
	pawn.setName("Bauern");
	recruitp.what = pawn;

	recruitp.costs = money;

	onPlayerAction(player2, &recruitp);

	//armies werden erstellt und zugewiesen

	EArmy army1;
	army1.setName("Armee Spieler 1");
	player1.addArmy(army1);

	EArmy army2;
	army2.setName("Armee Spieler 2");
	player2.addArmy(army2);

	army1.addTroop(infantry);
	army1.addTroop(pawn);
	army2.addTroop(pawn);
	army2.addTroop(infantry);

	army1.setCoords(rome.getCoords());
	army2.setCoords(athens.getCoords());

	army1.setAtk();



	//map->printMapStatus();

	//army1 wird bewegt

	AMove move1;
	move1.what = army1;
	move1.to = coordinates(2, 2);

	onPlayerAction(player1, &move1);

	//army2 wird bewegt

	AMove move2;
	move2.what = army2;
	move2.to = coordinates(0, 3);

	onPlayerAction(player2, &move2);


	AAttack attack1;
	attack1.what=army1;
	attack1.where=coordinates(0,3);

	onPlayerAction(player1,&attack1);

	onPlayerDisconnect(player1);
	onPlayerDisconnect(player2);


}



