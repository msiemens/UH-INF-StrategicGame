#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>

#include <iostream>
#include <list>

using namespace std;

// Network listeners
void GameClient::OnNetworkAction(GameActionPtr action){
 cout << "Ich bekomme etwas." << endl;
	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	AMove* move = dynamic_cast<AMove*>(action.get());
//	ABuild* build = dynamic_cast<ABuild*>(action.get());
//	AAttack* attack = dynamic_cast<AAttack*>(action.get());
	 cout << "Casten hat funktioniert." << endl;


	if (recruit != NULL) {
		 cout << "Es ist ein recruit!" << endl;
		if(recruit->inside == true){
			 cout << "inside" << endl;
			RecruitInside(recruit);
		}
	}
	if (move != NULL) {

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
