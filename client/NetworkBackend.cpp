#include "client/GameClient.h"

#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/AAttack.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>
#include <gamemodel/actions/ALogIn.h>

#include <iostream>
#include <list>

using namespace std;
void GameClient::SendLogIn(){
	ALogInPtr action(new ALogIn);
	action->verified=false;
	//action->id = player.getPlayerId();
	network.SendAction(action);
}

void GameClient::SendAttack(coordinates attacker, coordinates target){
	AAttackPtr action(new AAttack);
	action->attacker.x=attacker.x;
	action->attacker.y=attacker.y;
	action->target.x=target.x;
	action->target.y=target.y;

//send the action
	//OnNetworkAction(action);
	network.SendAction(action);
}

void GameClient::SendMoveArmy(int dir, int size){
//prepare the action to send
	AMovePtr action(new AMove);
	action->what = ArmySelected;
	action->from = ArmySelected->getCoords();
	action->count = size;
//if enough steps left
	if (size <= ArmySelected->GetStepsLeft()) {
		switch (dir) {
		case 0:
			action->to.x = ArmySelected->getCoords().x;
			action->to.y = ArmySelected->getCoords().y - size;
			break;
		case 1:
			action->to.x = ArmySelected->getCoords().x +  size;
			action->to.y = ArmySelected->getCoords().y;
			break;
		case 2:
			action->to.x = ArmySelected->getCoords().x;
			action->to.y = ArmySelected->getCoords().y +  size;
			break;
		case 3:
			action->to.x = ArmySelected->getCoords().x - size;
			action->to.y = ArmySelected->getCoords().y;
			break;
		}
//send the action
		//OnNetworkAction(action);
		network.SendAction(action);
	}
}

void GameClient::SendSetAP(coordinates coords) {

	ASetAPPtr action(new ASetAP);
	action->basecoords.x = PlaceSelected->getCoords().x;
	action->basecoords.y = PlaceSelected->getCoords().y;
	action->apcoords.x = coords.x;
	action->apcoords.y = coords.y;

	//OnNetworkAction(action);
	network.SendAction(action);
}

void GameClient::SendEndTurn() {
	subGS.SET_GameState(SUB_NONE);
	ArmySelected.reset();
	PlaceSelected.reset();
	ASetTurnPtr action(new ASetTurn);
	action->endturn = true;

	//OnNetworkAction(action);
	network.SendAction(action);
}

void GameClient::SendRecruitTroopInBuilding(EUnitPtr unit) {
	unit->setCoords(PlaceSelected->getCoords());

	ARecruitPtr action(new ARecruit);
	action->what = unit;
	action->base = PlaceSelected;
	action->inside = true;

	//OnNetworkAction(action);
	network.SendAction(action);
}

void GameClient::SendRecruitTroopOutside(EUnitPtr unit) {
	unit->setCoords(PlaceSelected->GetAssemblyPointCoords());

	ARecruitPtr action(new ARecruit);
	action->what = unit;
	action->base = PlaceSelected;
	action->inside = false;

	//OnNetworkAction(action);
	network.SendAction(action);
}
