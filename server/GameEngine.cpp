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

#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine(GameMapServer *map, GameContainer *container) :
		map(map),
		container(container),
		isRunning(true),
		logic(map, container),
		m_network(1337) {
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

    ALogInPtr logIn= boost::dynamic_pointer_cast<ALogIn>(action);


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
		onPlayerConnect(player);
		logIn->verified=true;
		GameActionPtr ret(logIn);
		m_network.SendAction(player,ret);

		if(container->getPlayerCount()> 1){
			if((rand()% 2) == 0){
				ASetTurnPtr setturn2(new ASetTurn);

				setturn2->endturn = false;
				m_network.SendAction(player,setturn2);

				setturn2->endturn = true;
				m_network.SendAction(player,setturn2);

			}else{
				ASetTurnPtr setturn2(new ASetTurn);

				setturn2->endturn = true;
				m_network.SendAction(player,setturn2);

				setturn2->endturn = false;
				m_network.SendAction(player,setturn2);
			}
		}

		if(container->getPlayerCount()==2){
			startSession();
		}
	}

	std::cout << "\n---------------------------------------------------------------\n";
}

void GameEngine::onNextTurn(){
	//reset StepsLeft
	for(auto army:*(container->getArmyListPtr())){
		army->SetStepsLeft(3);
	}
}

void GameEngine::createArmyAt(coordinates coords,PlayerPtr owner){
	map->setArmy(coords);
	EArmyPtr army(new EArmy);
	army->setCoords(coords);
	army->SetStepsLeft(3);
	army->SetOwner(owner->getPlayerId());

	container->addArmy(army);
}



GameActionPtr GameEngine::onPlayerRecruit(PlayerPtr player,ARecruitPtr recruit) {

			EUnitPtr unit(recruit->what);
			ELocationPtr base(map->getPlaceAt(recruit->base->getCoords()));
			GameRessourcePtr costs(recruit->costs);

			if(recruit->inside == true){
				base->town_army->AddUnit(unit);
				unit->SetOwner(player->getPlayerId());
			}else{
				if(map->isArmyPositioned(base->GetAssemblyPointCoords())==false){
					createArmyAt(base->GetAssemblyPointCoords(),player);
				}

//the new army object
				EArmyPtr armyat(map->getArmyAt(base->GetAssemblyPointCoords()));
//set coords of unit
				unit->setCoords(base->GetAssemblyPointCoords());
//unit added to player and army
				player->addUnit(unit);
				armyat->AddUnit(unit);

			}

			recruit->base=base;

			ARecruitPtr action(recruit);
			return action;
}


GameActionPtr GameEngine::onPlayerMove(PlayerPtr player,AMovePtr move) {

			GameEntityPtr what(move->what);
			coordinates from = what->getCoords();
			coordinates to = move->to;
			int size = move->count;

			EArmyPtr army(map->getArmyAt(from));

			if((army->GetStepsLeft() - size) >= 0){
				if(map->isBlocked(to) == false){
					if(map->isWalkable(to) == true and map->isPlace(to) == false and map->isArmyPositioned(to)==false){
						map->setWalkable(from);
						army->setCoords(to);
						map->setArmy(to);

						army->SetStepsLeft(army->GetStepsLeft() - size);
					}else if(map->isPlace(to) == true){
						//merge into place
						for(auto unit:army->units){
							map->getPlaceAt(to)->town_army->AddUnit(unit);
							army->RemoveUnit(unit);

							map->setWalkable(from);
							army->~EArmy();
						}
					}else if(map->isArmyPositioned(to) == true){
						//merge into army
						for(auto unit:army->units){
							map->getArmyAt(to)->AddUnit(unit);
							army->RemoveUnit(unit);

							map->setWalkable(from);
							army->~EArmy();
						}

					}
					army->SetStepsLeft(army->GetStepsLeft() - size);
				}
			}
			AMovePtr action(move);
			return action;

}


GameActionPtr GameEngine::onPlayerBuild(PlayerPtr player,ABuildPtr build) {
	EBuildingPtr building(build->what);
	ELocationPtr where(build->where);
	where->addBuilding(building);

	ABuildPtr action(build);
	return action;
}


GameActionPtr GameEngine::onPlayerAttack(PlayerPtr player,AAttackPtr attack) {
	attackArmy(map->getArmyAt(attack->attacker),map->getArmyAt(attack->target));
	return action;
}


GameActionPtr GameEngine::onPlayerSetAP(PlayerPtr player,ASetAPPtr setAP) {
	ELocationPtr place(map->getPlaceAt(setAP->basecoords));
	place->SetAssemblyPointCoords(setAP->apcoords);

	ASetAPPtr action(setAP);
	return action;
}

void GameEngine::onPlayerSetTurn(PlayerPtr player,ASetTurnPtr setTurn){

	if(setTurn->endturn == true){
		//player end the turn
		player->onturn = false;
		ASetTurnPtr setturn2(new ASetTurn);

		setturn2->endturn = true;
		m_network.SendAction(player,setturn2);

		if(container->getPlayerCount() > 1){
			setturn2->endturn = false;
			for(int i=0;i<container->getPlayerCount();i++){
				if(container->getPlayer(i)->getPlayerId() != player->getPlayerId()){
					m_network.SendAction(container->getPlayer(i),setturn2);
				}
			}
		}
	}else{
		//player start turn
		player->onturn = true;
		ASetTurnPtr setturn2(new ASetTurn);
		setturn2->endturn = false;
		m_network.SendAction(player,setturn2);

		if(container->getPlayerCount() > 1){
			setturn2->endturn = true;
			for(auto players : *(container->getPlayerListPtr())){
				if(players->getPlayerId() != player->getPlayerId()){
					m_network.SendAction(players,setturn2);
					break;
				}
			}
		}
	}
	onNextTurn();
}


void GameEngine::BroadcastAction(GameActionPtr action) {
	for(auto player:*(container->getPlayerListPtr())){
		m_network.SendAction(player,action);
	}
}

void GameEngine::startSession(){
	int counter=1;

	for(auto location:*(container->getLocationListPtr())){

		if(map->isStartBase(location->getCoords())){
			int i=1;
			for(auto player:*(container->getPlayerListPtr())){
				if(counter==i){
					player->addLocation(location);
					//das kann auch in playerfkt addLocation
					location->owned=true;
					location->SetOwner(player->getPlayerId());
					//--------------------------------------
				}
				counter++;
			}
			counter=0;
		}
	}
}

void GameEngine::attackArmy(EArmyPtr attacker, EArmyPtr defender) {

}

void GameEngine::run() {
	m_network.ConnectOnAction(boost::bind(&GameEngine::onPlayerAction, this, _1, _2));
	m_network.thread()->join();
}
