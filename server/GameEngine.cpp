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

GameEngine::GameEngine(GameMap *map, list<PlayerPtr> playerlist) :
		map(map),
		playerlist(playerlist),
		isRunning(true),
		logic(map, playerlist),
		m_network(1337) {
	// test();
	m_network.ConnectOnAction(boost::bind(&GameEngine::onPlayerAction, this, _1));
}

GameEngine::~GameEngine() {
}

bool GameEngine::onPlayerConnect(PlayerPtr player) {
	//std::cout << "\nSpieler mit ID "<< player->getPlayerId() << " hat sich connected";
	playerlist.insert(playerlist.end(), player);
	return true;
}

void GameEngine::onPlayerDisconnect(PlayerPtr player) {
}

void GameEngine::onPlayerAction(/* PlayerPtr player, */ GameActionPtr action) {
	// if (logic.checkPlayerAction(player, action) == true) {
	doAction(player, action);
	// } else {
	// cout << "Requested action of #" << player->playerId << " is invalid" << endl;
	// }

}

void GameEngine::doAction(PlayerPtr player, GameActionPtr action) {

	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	AMove* move = dynamic_cast<AMove*>(action.get());
	ABuild* build = dynamic_cast<ABuild*>(action.get());
	AAttack* attack = dynamic_cast<AAttack*>(action.get());

	if (recruit != NULL) {

		ETroopsPtr troops(recruit->what);
		EPlacePtr base(recruit->base);
		GameRessourcePtr costs(recruit->costs);

		player->addTroops(troops);

		//std::cout << "\nSpieler "<< player->getPlayerId() << " rekrutiert " << troops.getName() << " in " <<
		//	base.getName();

	}
	if (move != NULL) {
		cout << ":: Got move command" << endl;
		GameEntityPtr what(move->what);

		coordinates from = what->getCoords();
		coordinates to = move->to;
		cout << ":: Moving from " << from.x << "/" << from.y << " to " << to.x
				<< "/" << to.y << endl;

		//map->printMapStatus();

		// map->setArmy(to);
		// map->isWalkable(from);

		what->setCoords(to);

		int x = what->getCoords().x;
		int y = what->getCoords().y;
		cout << ":: New coordinates: " << x << "/" << y << endl;

	}
	if (build != NULL) {
		EBuildingPtr building(build->what);
		EPlacePtr where(build->where);
		where->addBuilding(building);

		//std::cout << "\nSpieler "<<player->getPlayerId() << " baut " << building.getName() << " in "
		//	<< where.getName();

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

	PlayerPtr player1(new Player());
	PlayerPtr player2(new Player());

	onPlayerConnect(player1);
	onPlayerConnect(player2);

	EPlacePtr rome(new EMetropolis);
	EPlacePtr athens(new EMetropolis);

	rome->setName("Rom");
	athens->setName("Athen");

	rome->setCoords(coordinates(0, 0));
	athens->setCoords(coordinates(3, 3));
	rome->inhabitans = 100;
	athens->inhabitans = 100;

	player1->addPlace(rome);
	player2->addPlace(athens);

	map->setPlace(rome->getCoords());
	map->setPlace(athens->getCoords());

	//map->printMapStatus();

	//P1 baut Kaserne in place rome

	ABuildPtr buildcinrome(new ABuild);
	buildcinrome->where = rome;

	EBuildingPtr casernir(new ECasern);
	casernir->setName("Kaserne");
	buildcinrome->what = casernir;

	GameRessourcePtr money(new RMoney);
	buildcinrome->costs = money;

	onPlayerAction(player1, buildcinrome);

	//P2 baut Kaserne in place athens

	ABuildPtr buildcinathens(new ABuild);
	buildcinathens->where = athens;

	EBuildingPtr casernia(new ECasern);
	casernia->setName("Kaserne");
	buildcinathens->what = casernia;

	onPlayerAction(player2, buildcinathens);

	//P1 rekrutiert Infantrie in place rome

	ARecruitPtr recruiti(new ARecruit);
	recruiti->base = rome;

	ETroopsPtr infantry(new EInfantry);
	infantry->setName("Infantrie");
	recruiti->what = infantry;

	onPlayerAction(player1, recruiti);

	//P2 rekrutiert Bauern in place athens
	ARecruitPtr recruitp(new ARecruit);
	recruitp->base = athens;

	ETroopsPtr pawn(new EPawn);
	pawn->setName("Bauern");
	recruitp->what = pawn;
	recruitp->costs = money;

	onPlayerAction(player2, recruitp);

	//armies werden erstellt und zugewiesen
	EArmyPtr army1(new EArmy);

	army1->setName("Armee Spieler 1");
	player1->addArmy(army1);

	EArmyPtr army2(new EArmy);

	army2->setName("Armee Spieler 2");
	player2->addArmy(army2);

	army1->addTroop(infantry);
	army1->addTroop(pawn);
	army2->addTroop(pawn);
	army2->addTroop(infantry);

	army1->setCoords(rome->getCoords());
	army2->setCoords(athens->getCoords());

	army1->setAtk();

	//map->printMapStatus();

	//army1 wird bewegt
	AMovePtr move1(new AMove);
	move1->what = army1;
	move1->to = coordinates(2, 2);

	std::cout << "Moving parmy1 from " << army1->getCoords().x << "/"
			<< army1->getCoords().y << " to " << move1->to.x << "/"
			<< move1->to.y << std::endl;
	onPlayerAction(player1, move1);
	std::cout << "New coords of parmy1 " << army1->getCoords().x << "/"
			<< army1->getCoords().y << std::endl;

	AMovePtr move2(new AMove);
	move2->what = army2;
	move2->to = coordinates(0, 3);

	std::cout << "Moving parmy1 from " << army2->getCoords().x << "/"
			<< army2->getCoords().y << " to " << move2->to.x << "/"
			<< move2->to.y << std::endl;
	onPlayerAction(player2, move2);
	std::cout << "New coords of parmy2 " << army2->getCoords().x << "/"
			<< army2->getCoords().y << std::endl;

	AAttackPtr attack1(new AAttack);
	attack1->what = army1;
	attack1->where = coordinates(0, 3);

	onPlayerAction(player1, attack1);

	onPlayerDisconnect(player1);
	onPlayerDisconnect(player2);

}

