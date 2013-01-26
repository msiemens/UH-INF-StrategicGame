#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ALogIn.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>


#include "network/messages/statemessages/SMUpdateRessources.h"
#include "network/messages/statemessages/SMUpdateUUID.h"
#include "network/messages/statemessages/SMSetStartBase.h"
#include "network/messages/statemessages/SMUpdateActionsLeft.h"
#include "network/messages/statemessages/SMBattleResult.h"
#include "network/messages/statemessages/SMSetLocationOwner.h"

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
	SMUpdateUUID* uuid =  dynamic_cast<SMUpdateUUID*>(message.get());
	SMSetStartBase* setstartbase = dynamic_cast<SMSetStartBase*>(message.get());
	SMUpdateActionsLeft* updateactionsleft = dynamic_cast<SMUpdateActionsLeft*>(message.get());
	SMBattleResult* battle_result = dynamic_cast<SMBattleResult*>(message.get());
	SMSetLocationOwner* set_location_owner = dynamic_cast<SMSetLocationOwner*>(message.get());

	cout << "hier 11111" << endl;
	if(updateress != NULL){
		player.setGold(updateress->gold);
		player.setWood(updateress->wood);
		player.setStone(updateress->stone);
	}
	if(uuid != NULL){
		player.setPlayerId(uuid->id);
	}
	if(setstartbase != NULL){
		ELocationPtr location(map.getPlaceAt(setstartbase->coords));
		location->SetOwner(player.getPlayerId());
	}
	if(updateactionsleft != NULL){
		player.SetActionLeft(updateactionsleft->actions_left);
	}
	if(battle_result != NULL){
		cout << "hier 22222" << endl;
		map.setWalkable(battle_result->looser->getCoords());

		if(battle_result->winner->GetOwner() == player.getPlayerId()){
			cout << "hier 333333" << endl;
			opponent.armies.remove(getOpponentArmyByCoords(battle_result->looser->getCoords()));
			player.armies.remove(getArmyByCoords(battle_result->winner->getCoords()));
			if(battle_result->looser->units.size() > 0){
				cout << "hier 44444" << endl;
				battle_result->looser->setImgPath("client/gfx/entity/army_opp.png");
				opponent.addArmy(battle_result->looser);
			}
			player.addArmy(battle_result->winner);
			cout << "hier 5555555555555" << endl;
		}else{
			cout << "hier 333333" << endl;
			opponent.armies.remove(getOpponentArmyByCoords(battle_result->winner->getCoords()));
			player.armies.remove(getArmyByCoords(battle_result->looser->getCoords()));

			if(battle_result->looser->units.size() > 0){
				cout << "hier 44444" << endl;
				player.addArmy(battle_result->looser);
			}
			battle_result->winner->setImgPath("client/gfx/entity/army_opp.png");
			opponent.addArmy(battle_result->winner);
			cout << "hier 5555555555555" << endl;
		}
	}
	if(set_location_owner != NULL){
		ELocationPtr location(map.getPlaceAt(set_location_owner->coords));
		location->SetOwner(set_location_owner->owner);
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
		if(place->GetOwner() != player.id){//verhindert dass der player seine truppen in gegnerische st�dte platziert
			action->what->SetOwner(opponent.getPlayerId());
			place->town_army->AddUnit(action->what);
		}
	}
}

void GameClient::RecruitOutside(ARecruit* action){
	//Myturn
	if(player.onturn and action->what->GetOwner() == player.getPlayerId()){ // action->what->GetOwner() == player.getPlayerId() and
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
			army->SetStepsLeft(2);
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
			army->SetStepsLeft(2);
			army->setCoords(action->base->GetAssemblyPointCoords());
			army->SetOwner(opponent.getPlayerId());
			opponent.armies.insert(opponent.armies.end(), army);
			map.setArmy(action->base->GetAssemblyPointCoords());
		}
	}
}
