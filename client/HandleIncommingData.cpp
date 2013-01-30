#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ALogIn.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>


#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/bind.hpp>

#include <network/ClientNetwork.h>

#include "network/messages/statemessages/SMUpdateRessources.h"
#include "network/messages/statemessages/SMUpdateUUID.h"
#include "network/messages/statemessages/SMSetStartBase.h"
#include "network/messages/statemessages/SMUpdateActionsLeft.h"
#include "network/messages/statemessages/SMBattleResult.h"
#include "network/messages/statemessages/SMSetLocationOwner.h"
#include "network/messages/statemessages/SMUpdateArmy.h"
#include "network/messages/statemessages/SMRemoveArmy.h"
#include "network/messages/statemessages/SMUpdateLocationArmy.h"

#include <iostream>
#include <list>

using namespace std;

// Network listeners
void GameClient::OnNetworkAction(GameActionPtr action){
	ASetAPPtr setAP = boost::dynamic_pointer_cast<ASetAP>(action);
	ARecruitPtr recruit = boost::dynamic_pointer_cast<ARecruit>(action);
	AMovePtr move = boost::dynamic_pointer_cast<AMove>(action);
	ASetTurnPtr setTurn = boost::dynamic_pointer_cast<ASetTurn>(action);
	ALogInPtr login = boost::dynamic_pointer_cast<ALogIn>(action);

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
	SMUpdateArmy* update_army = dynamic_cast<SMUpdateArmy*>(message.get());
	SMRemoveArmy* remove_army = dynamic_cast<SMRemoveArmy*>(message.get());
	SMUpdateLocationArmy* update_loc_army = dynamic_cast<SMUpdateLocationArmy*>(message.get());

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

		if(battle_result->winner->GetOwner() == player.getPlayerId()){
			opponent.armies.remove(getOpponentArmyByCoords(battle_result->looser_coords));
			player.armies.remove(getArmyByCoords(battle_result->winner->getCoords()));
//			if(battle_result->looser->units.size() > 0){
//				battle_result->looser->setImgPath("client/gfx/entity/army_opp.png");
//				opponent.addArmy(battle_result->looser);
//			}else{
				map.setWalkable(battle_result->looser_coords);
			//}
			player.addArmy(battle_result->winner);
		}else{
			opponent.armies.remove(getOpponentArmyByCoords(battle_result->winner->getCoords()));
			player.armies.remove(getArmyByCoords(battle_result->looser_coords));

//			if(battle_result->looser->units.size() > 0){
//				player.addArmy(battle_result->looser);
//			}else{
				map.setWalkable(battle_result->looser_coords);
			//}
			battle_result->winner->setImgPath("client/gfx/entity/army_opp.png");
			opponent.addArmy(battle_result->winner);
		}
	}
	if(set_location_owner != NULL){
		ELocationPtr location(map.getPlaceAt(set_location_owner->coords));
		location->SetOwner(set_location_owner->owner);
		location->owned = true;
	}


	if(update_army != NULL){
		if(update_army->army->GetOwner() == player.getPlayerId()){
			update_army->army->SetOwner(player.getPlayerId());
			player.armies.remove(getArmyByCoords(update_army->army->getCoords()));
			player.addArmy(update_army->army);
			ArmySelected = getArmyByCoords(update_army->army->getCoords());
		}else{
			opponent.armies.remove(getOpponentArmyByCoords(update_army->army->getCoords()));
			opponent.addArmy(update_army->army);
			getOpponentArmyByCoords(update_army->army->getCoords())->SetOwner(opponent.getPlayerId());
		}
	}
	if(remove_army != NULL){
		if(remove_army->owner == player.getPlayerId()){
			player.armies.remove(getArmyByCoords(remove_army->coords));
			map.setWalkable(remove_army->coords);
		}else{
			opponent.armies.remove(getOpponentArmyByCoords(remove_army->coords));
			map.setWalkable(remove_army->coords);
		}
	}
	if(update_loc_army != NULL){
		if(map.getPlaceAt(update_loc_army->coords)->GetOwner() == player.getPlayerId()){
			for(auto unit: update_loc_army->army->units){
				map.getPlaceAt(update_loc_army->coords)->town_army->units.push_back(unit);
			}
		}else{
			for(auto unit: update_loc_army->army->units){
				map.getPlaceAt(update_loc_army->coords)->town_army->units.push_back(unit);
			}
		}
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

void GameClient::ReceiveLogIn(ALogInPtr login){
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

void GameClient::ReceiveMoveArmy(AMovePtr move){
//if moveable...move
	if(player.onturn){
		if(map.isWalkable(move->to) == true and map.isPlace(move->to) == false and map.isArmyPositioned(move->to)==false){
			map.setWalkable(ArmySelected->getCoords());
			ArmySelected->setCoords(move->to);
			map.setArmy(ArmySelected->getCoords());
			if(ArmySelected->GetStepsLeft() == 0){
				subGS.SET_GameState(SUB_NONE);
			}
		}

		//remove Stepsleft
		ArmySelected->SetStepsLeft( ArmySelected->GetStepsLeft() - move->count);
	}else if(opponent.onturn){
		EArmyPtr army(getOpponentArmyByCoords(move->from));

		if(map.isWalkable(move->to) == true and map.isPlace(move->to) == false and map.isArmyPositioned(move->to)==false){
			map.setWalkable(army->getCoords());
			army->setCoords(move->to);
			map.setArmy(army->getCoords());
		}

		//remove Stepsleft
		army->SetStepsLeft( army->GetStepsLeft() - move->count);
	}
}

void GameClient::RecruitInside(ARecruitPtr action){
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

void GameClient::RecruitOutside(ARecruitPtr action){
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
