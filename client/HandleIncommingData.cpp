#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ALogIn.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>


#include "network/messages/statemessages/SMUpdateRessources.h"

#include <iostream>
#include <list>

using namespace std;

// Network listeners
void GameClient::OnNetworkAction(GameActionPtr action){
	ARecruit* recruit = dynamic_cast<ARecruit*>(action.get());
	AMove* move = dynamic_cast<AMove*>(action.get());
	ASetAP* setAP = dynamic_cast<ASetAP*>(action.get());
	ASetTurn* setTurn = dynamic_cast<ASetTurn*>(action.get());
	ALogIn* login = dynamic_cast<ALogIn*>(action.get());

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
	if (setTurn != NULL) {
		ReceiveSetTurn(setTurn->endturn);
	}
	if(login != NULL){
		ReceiveLogIn(login);
	}
}

void GameClient::OnNetworkMessage(GameStateMessagePtr message){
	SMUpdateRessources* updateress = dynamic_cast<SMUpdateRessources*>(message.get());

	if(updateress != NULL){
		player.setGold(updateress->gold);
		player.setWood(updateress->wood);
		player.setStone(updateress->stone);
	}
}

void GameClient::ReceiveSetTurn(bool endturn){
	if(endturn==true){
		player.onturn = false;
		opponent.onturn = true;
	}else{
		player.onturn = true;
		opponent.onturn = false;
	}
	OnNextTurn();
}

void GameClient::ReceiveSetAP(ELocationPtr place, coordinates coords){
	place->SetAssemblyPointCoords(coords);
}

void GameClient::ReceiveLogIn(ALogIn* login){
	if(login->verified){
		//if(login->id == player.getPlayerId()){
			ingame = true;
			//Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_FULLSCREEN | SDL_HWSURFACE);
//		}else{
//			cout << "fail" << endl;
//			cout << "Opponent joined the game." << endl;
//		}
	}
}

void GameClient::ReceiveMoveArmy(AMove* move){
//if moveable...move
	if(player.onturn){
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

		//remove Stepsleft
		ArmySelected->SetStepsLeft( ArmySelected->GetStepsLeft() - move->count);
	}else if(opponent.onturn){
		EArmyPtr army(getOpponentArmyByCoords(move->from));

		if(map.isWalkable(move->to) == true and map.isPlace(move->to) == false and map.isArmyPositioned(move->to)==false){
			map.setWalkable(army->getCoords());
			army->setCoords(move->to);
			map.setArmy(army->getCoords());
		}else if(map.isPlace(move->to) == true){
			//if there is a place, merge into(if possible)
			MergeArmyIntoPlace(move->to, army);
		}else if(map.isArmyPositioned(move->to) == true){
			MergeArmies(move->to, army);
		}

		//remove Stepsleft
		army->SetStepsLeft( army->GetStepsLeft() - move->count);
	}
}

void GameClient::RecruitInside(ARecruit* action){
	//Myturn
	ELocationPtr place = map.getPlaceAt(action->base->getCoords());

	if(player.onturn){
		//if(place->GetOwner() == player.id){
			action->what->SetOwner(player.getPlayerId());
			place->town_army->AddUnit(action->what);
		//}
	}else if(opponent.onturn){
		if(place->GetOwner() != player.id){//verhindert dass der player seine truppen in gegnerische städte platziert
			action->what->SetOwner(opponent.getPlayerId());
			place->town_army->AddUnit(action->what);
		}
	}
}

void GameClient::RecruitOutside(ARecruit* action){
	//Myturn
	if(player.onturn){ // action->what->GetOwner() == player.getPlayerId() and
		if (map.isArmyPositioned(action->base->GetAssemblyPointCoords())) {
			for (auto army : player.armies){
				if (army->getCoords().x == action->base->GetAssemblyPointCoords().x
						and army->getCoords().y == action->base->GetAssemblyPointCoords().y) {
					action->what->SetOwner(player.getPlayerId());
					army->AddUnit(action->what);
				}
			}
		} else {
			EArmyPtr army(new EArmy);
			army->setImgPath("client/gfx/entity/army.png");

			army->SetOwner(player.getPlayerId());
			action->what->SetOwner(player.getPlayerId());
			army->AddUnit(action->what);
			army->SetStepsLeft(3);
			army->setCoords(action->base->GetAssemblyPointCoords());
			army->SetOwner(player.getPlayerId());
			player.armies.insert(player.armies.end(), army);
			map.setArmy(action->base->GetAssemblyPointCoords());
		}
	}else if (opponent.onturn){//Opponents turn
		if (map.isArmyPositioned(action->base->GetAssemblyPointCoords())) {
			for (auto army : opponent.armies){
				if (army->getCoords().x == action->base->GetAssemblyPointCoords().x
						and army->getCoords().y == action->base->GetAssemblyPointCoords().y) {
					action->what->SetOwner(opponent.getPlayerId());
					army->AddUnit(action->what);
				}
			}
		} else {
			EArmyPtr army(new EArmy);
			army->setImgPath("client/gfx/entity/army_opp.png");
			army->AddUnit(action->what);
			army->SetStepsLeft(3);
			army->setCoords(action->base->GetAssemblyPointCoords());
			army->SetOwner(opponent.getPlayerId());
			opponent.armies.insert(opponent.armies.end(), army);
			map.setArmy(action->base->GetAssemblyPointCoords());
		}
	}
}
