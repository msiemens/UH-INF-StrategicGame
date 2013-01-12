#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>

#include <iostream>
#include <list>

using namespace std;

// Network listeners
void GameClient::OnNetworkAction(GameActionPtr action){
	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	AMove* move = dynamic_cast<AMove*>(action.get());
	ASetAP* setAP = dynamic_cast<ASetAP*>(action.get());

	if (recruit != NULL) {
		if(recruit->inside == true){
			RecruitInside(recruit);
		}else{
			RecruitOutside(recruit);
		}
	}

	if (move != NULL) {
		ReceiveMoveArmy(move);
	}

	if (setAP != NULL) {
		ReceiveSetAP(map.getPlaceAt(setAP->basecoords), setAP->apcoords);
	}
}

void GameClient::OnNetworkMessage(GameStateMessagePtr message){}

void GameClient::ReceiveSetAP(ELocationPtr place, coordinates coords){
	place->SetAssemblyPointCoords(coords);
}

void GameClient::ReceiveMoveArmy(AMove* move){
//if moveable...move
	if(map.isWalkable(move->to) == true and map.isPlace(move->to) == false and map.isArmyPositioned(move->to)==false){
		map.setWalkable(ArmySelected->getCoords());
		ArmySelected->setCoords(move->to);
		map.setArmy(ArmySelected->getCoords());
		if(ArmySelected->GetStepsLeft() == 0){
			subGS.SET_GameState(SUB_NONE);
		}
	}else if(map.isPlace(move->to) == true){
//if there is a place, merge into(if possible)
		MergeArmyIntoPlace(move->to, ArmySelected);
		subGS.SET_GameState(SUB_NONE);
	}else if(map.isArmyPositioned(move->to) == true){
		MergeArmies(move->to, ArmySelected);
		subGS.SET_GameState(SUB_NONE);
	}
}

void GameClient::RecruitInside(ARecruit* action){
	//Myturn
	ELocationPtr place = map.getPlaceAt(action->base->getCoords());

	if(onturn){
		//if(place->GetOwner() == player.id){
			place->town_army->AddTroop(action->what);
		//}
	}else{
		if(place->GetOwner() != player.id){//verhindert dass der player seine truppen in gegnerische städte platziert
			place->town_army->AddTroop(action->what);
		}
	}
}

void GameClient::RecruitOutside(ARecruit* action){
	//Myturn
	if(onturn){
		if (map.isArmyPositioned(action->base->GetAssemblyPointCoords())) {
			for (auto army : player.armies){
				if (army->getCoords().x == action->base->GetAssemblyPointCoords().x
						and army->getCoords().y == action->base->GetAssemblyPointCoords().y) {
					army->AddTroop(action->what);
				}
			}
		} else {
			EArmyPtr army(new EArmy);
			army->setImgPath("client/gfx/entity/army.png");
			army->AddTroop(action->what);
			army->SetStepsLeft(3);
			army->setCoords(action->base->GetAssemblyPointCoords());
			player.armies.insert(player.armies.end(), army);
			map.setArmy(action->base->GetAssemblyPointCoords());
		}
	}else{//Opponents turn
		if (map.isArmyPositioned(action->base->GetAssemblyPointCoords())) {
			for (auto army : opponent.armies){
				if (army->getCoords().x == action->base->GetAssemblyPointCoords().x
						and army->getCoords().y == action->base->GetAssemblyPointCoords().y) {
					army->AddTroop(action->what);
				}
			}
		} else {
			EArmyPtr army(new EArmy);
			army->setImgPath("client/gfx/entity/army.png");
			army->AddTroop(action->what);
			army->SetStepsLeft(3);
			army->setCoords(action->base->GetAssemblyPointCoords());
			opponent.armies.insert(player.armies.end(), army);
			map.setArmy(action->base->GetAssemblyPointCoords());
		}
	}
}
