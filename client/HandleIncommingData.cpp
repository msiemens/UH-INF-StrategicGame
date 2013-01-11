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
		}
	}

	if (move != NULL) {

	}

	if (setAP != NULL) {
		ELocationPtr place(map.getPlaceAt(setAP->basecoords));
		place->SetAssemblyPointCoords(setAP->apcoords);
	}
}
void GameClient::OnNetworkMessage(GameStateMessagePtr message){

}

void GameClient::RecruitInside(ARecruit* action){
	//Myturn
	ELocationPtr place = map.getPlaceAt(action->base->getCoords());

	if(onturn){
		if(place->GetOwner() == player.id){
			place->town_army->AddTroop(action->what);
		}
	}else{
		if(place->GetOwner() != player.id){//verhindert dass der player seine truppen in gegnerische st�dte platziert
			place->town_army->AddTroop(action->what);
		}
	}
}

void GameClient::RecruitOutside(ARecruitPtr action){
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
