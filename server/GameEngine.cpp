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

#include <network/ServerNetwork.h>
#include <network/messages/statemessages/SMUpdateRessources.h>

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
	map->printMapStatus();
	std::cout << "\nSpieler mit ID "<< player->getPlayerIdStr() << " hat sich connected" << endl;
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
		std::cout << "Action ausgef�hrt.\n";
	} else {
		std::cout << "Action von Spieler #" << player->getPlayerIdStr()
				<< " ist ungueltig.\n";
	}
}
void GameEngine::SendUpdateRessources(PlayerPtr player){
	SMUpdateRessourcesPtr updatres(new SMUpdateRessources);
	updatres->gold=player->getGold();
	updatres->wood=player->getWood();
	updatres->stone=player->getStone();
	GameStateMessagePtr message(updatres);
	m_network.SendMessageA(player,message);
}

void GameEngine::doAction(PlayerPtr player, GameActionPtr action) {
	std::cout << "---------------------------------------------------------------\n";
	std::cout << "GameEngine::doAction(...).\n";

	/*
	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	ASetAP* setAP = dynamic_cast<ASetAP*>(action.get());
	ASetTurn* setTurn = dynamic_cast<ASetTurn*>(action.get());

	AMove* move = dynamic_cast<AMove*>(action.get());
	ABuild* build = dynamic_cast<ABuild*>(action.get());
	AAttack* attack = dynamic_cast<AAttack*>(action.get());

	ALogIn* logIn= dynamic_cast<ALogIn*>(action.get());

	// */

    ARecruitPtr recruit = boost::dynamic_pointer_cast<ARecruit>(action);
    ASetAPPtr setAP = boost::dynamic_pointer_cast<ASetAP>(action);
    ASetTurnPtr setTurn = boost::dynamic_pointer_cast<ASetTurn>(action);

    AMovePtr move = boost::dynamic_pointer_cast<AMove>(action);
    ABuildPtr build = boost::dynamic_pointer_cast<ABuild>(action);
    AAttackPtr attack = boost::dynamic_pointer_cast<AAttack>(action);

    ALogInPtr logIn= boost::dynamic_pointer_cast<ALogIn>(action);


	std::cout << "GameEngine::doAction: checking type.\n";
	if (recruit != NULL) {
		BroadcastAction(onPlayerRecruit(player,recruit));
	}
	if(setAP != NULL){
		BroadcastAction(onPlayerSetAP(player,setAP));
	}
	if(setTurn != NULL){
		onPlayerSetTurn(player,setTurn);
	}
	if (move != NULL) {
		BroadcastAction(onPlayerMove(player,move));
	}
	if (build != NULL) {
		BroadcastAction(onPlayerBuild(player,build));
	}
	if (attack != NULL) {
		BroadcastAction(onPlayerAttack(player,attack));
	}
	if(logIn != NULL){
		onPlayerLogIn(player,logIn);
	}

	std::cout << "\n---------------------------------------------------------------\n";
}
void GameEngine::onPlayerLogIn(PlayerPtr player, ALogInPtr logIn){

	onPlayerConnect(player);
	logIn->verified=true;
	GameActionPtr ret(logIn);
	m_network.SendAction(player,ret);

	if(playerlist->size() > 1){
		if((rand()% 2) == 0){
			ASetTurnPtr setturn2(new ASetTurn);

			setturn2->endturn = false;
			m_network.SendAction(player,setturn2);

			setturn2->endturn = true;
			for(auto players : *playerlist){
				if(players->getPlayerIdStr() != player->getPlayerIdStr()){
					m_network.SendAction(players,setturn2);
					//dies funktioniert nur f�r 2 spieler!
					break;
				}
			}
		}else{
			ASetTurnPtr setturn2(new ASetTurn);

			setturn2->endturn = true;
			m_network.SendAction(player,setturn2);

			setturn2->endturn = false;
			for(auto players : *playerlist){
				if(players->getPlayerIdStr() != player->getPlayerIdStr()){
					m_network.SendAction(players,setturn2);
					//dies funktioniert nur f�r 2 spieler!
					break;
				}
			}
		}
	}
	if(playerlist->size()==2){
		startSession();
		for(auto player : *playerlist){
			for(auto place: player->places){
				std::cout << "Location von Spieler " << player->getPlayerIdStr() << "X:" << place->getCoords().x << ", Y:" << place->getCoords().y << endl;
			}
		}
	}
}
void GameEngine::onNextTurn(){
	//reset StepsLeft
	for(auto player : *playerlist){
		for(auto army : player->armies){
			army->SetStepsLeft(3);
		}
	}
}

void GameEngine::createArmyAt(coordinates coords,PlayerPtr owner){
	map->setArmy(coords);
	EArmyPtr army(new EArmy);
	army->setCoords(coords);
	army->SetStepsLeft(3);
	owner->addArmy(army);
}

GameActionPtr GameEngine::onPlayerRecruit(PlayerPtr player,ARecruitPtr recruit) {
	std::cout << "GameEngine::doAction: got a ARecruit.\n";

			if(recruit->inside == true){

				EUnitPtr unit(recruit->what);
				ELocationPtr base(map->getPlaceAt(recruit->base->getCoords()));
				GameRessourcePtr costs(recruit->costs);

				base->town_army->AddUnit(unit);
				player->addUnit(unit);
				recruit->base=base;
				unit->SetOwner(player->getPlayerId());



				std::cout << "GameEngine::doAction: successful.\n";

			}else{
				EUnitPtr unit(recruit->what);
				ELocationPtr base(map->getPlaceAt(recruit->base->getCoords()));
				GameRessourcePtr costs(recruit->costs);

				if(map->isArmyPositioned(base->GetAssemblyPointCoords())==false){
					createArmyAt(base->GetAssemblyPointCoords(),player);
				}

				EArmyPtr armyat(logic.getArmyAt(base->GetAssemblyPointCoords()));
				unit->setCoords(base->GetAssemblyPointCoords());
				player->addUnit(unit);
				armyat->AddUnit(unit);

				recruit->base=base;

				std::cout << "GameEngine::doAction: successful.\n";
			}

			ARecruitPtr action(recruit);
			return action;
}

GameActionPtr GameEngine::onPlayerMove(PlayerPtr player,AMovePtr move) {
	std::cout << "GameEngine::doAction: got a AMove.\n";
			GameEntityPtr what(move->what);

			coordinates from = what->getCoords();
			coordinates to = move->to;
			int size = move->count;
			EArmyPtr army(logic.getArmyAt(from));

			if((army->GetStepsLeft() - size) >= 0){
				if(map->isBlocked(to) == false){
					if(map->isWalkable(to) == true and map->isPlace(to) == false and map->isArmyPositioned(to)==false){
						map->setWalkable(from);
						army->setCoords(to);
						map->setArmy(to);
					}else if(map->isPlace(to) == true){
						//merge into place
					}else if(map->isArmyPositioned(to) == true){
						//merge into army
					}
					army->SetStepsLeft(army->GetStepsLeft() - size);
				}
			}
			AMovePtr action(move);
			return action;

}

GameActionPtr GameEngine::onPlayerBuild(PlayerPtr player,ABuildPtr build) {
	std::cout << "GameEngine::doAction: got a ABuild.\n";
	EBuildingPtr building(build->what);
	ELocationPtr where(build->where);
	where->addBuilding(building);

	ABuildPtr action(build);
	return action;
}

GameActionPtr GameEngine::onPlayerAttack(PlayerPtr player,AAttackPtr attack) {
	std::cout << "GameEngine::doAction: got a AAttack.\n";
	GameEntityPtr what(attack->what);
	coordinates where = attack->target;

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
	AAttackPtr action(attack);
	return action;
}

GameActionPtr GameEngine::onPlayerSetAP(PlayerPtr player,ASetAPPtr setAP) {
	std::cout << "GameEngine::doAction: got a ASetAP.\n";
	ASetAPPtr setAP2(new ASetAP);
	setAP2->apcoords.x = setAP->apcoords.x;
	setAP2->apcoords.y = setAP->apcoords.y;
	setAP2->basecoords.x = setAP->basecoords.x;
	setAP2->basecoords.y = setAP->basecoords.y;

	ELocationPtr place(map->getPlaceAt(setAP->basecoords));
	place->SetAssemblyPointCoords(setAP->apcoords);

	ASetAPPtr action(setAP);
	return action;
}

void GameEngine::onPlayerSetTurn(PlayerPtr player,ASetTurnPtr setTurn){

	std::cout << "GameEngine::doAction: got a ASetTurn.\n";

	if(setTurn->endturn == true){
		//player end the turn
		player->onturn = false;
		ASetTurnPtr setturn2(new ASetTurn);

		setturn2->endturn = true;
		m_network.SendAction(player,setturn2);

		if(playerlist->size() > 1){
		// opponnent's on turn
			setturn2->endturn = false;
			for(auto players : *playerlist){
				if(players->getPlayerIdStr() != player->getPlayerIdStr()){
					m_network.SendAction(players,setturn2);
					//dies funktioniert nur f�r 2 spieler!
					break;
				}
			}
		}
	}else{
		//player start turn
		player->onturn = true;
		ASetTurnPtr setturn2(new ASetTurn);
		setturn2->endturn = false;
		m_network.SendAction(player,setturn2);

		if(playerlist->size() > 1){
			setturn2->endturn = true;
			for(auto players : *playerlist){
				if(players->getPlayerIdStr() != player->getPlayerIdStr()){
					m_network.SendAction(players,setturn2);
					//dies funktioniert nur f�r 2 spieler!
					break;
				}
			}
		}
	}
	onNextTurn();
}


void GameEngine::BroadcastAction(GameActionPtr action) {
	for(auto player:*playerlist){
		m_network.SendAction(player,action);
	}
}

void GameEngine::startSession(){
	int counter=1;
	for(auto place:map->placeList){
		if(map->isStartBase(place->getCoords())){

			int i=1;
			for(auto player:*playerlist){
				if(counter==i){
					player->addLocation(place);
					place->owned=true;
					place->SetOwner(player->getPlayerId());
				}
				counter++;
			}
			counter=0;
		}
	}
}

void GameEngine::run() {
	m_network.ConnectOnAction(boost::bind(&GameEngine::onPlayerAction, this, _1, _2));
	m_network.thread()->join();
}
