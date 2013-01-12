#include "client/GameClient.h"

#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>

#include <iostream>
#include <list>

using namespace std;

void GameClient::SendMoveArmy(int dir, int size){
//prepare the action to send
	AMovePtr action(new AMove);
	action->what = ArmySelected;
	action->from = ArmySelected->getCoords();
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
//remove Stepsleft
		ArmySelected->SetStepsLeft( ArmySelected->GetStepsLeft() - size);
//send the action

		OnNetworkAction(action);
		//network.SendAction(action);
	}
}

void GameClient::RecruitTroopInBuilding() {
	EUnitPtr troop1(new EUnit);
	troop1->setCoords(12,12);

	ARecruitPtr action(new ARecruit);
	action->what = troop1;
	action->base = PlaceSelected;
	action->inside = true;

	//OnNetworkAction(action);
	network.SendAction(action);
}

void GameClient::RecruitTroopOutside(coordinates coords) {
	EUnitPtr troop1(new EUnit);

	ARecruitPtr action(new ARecruit);
	action->what = troop1;
	action->base = PlaceSelected;
	action->inside = false;

	OnNetworkAction(action);
	//network.SendAction(action);
}

void GameClient::MergeArmyIntoPlace(coordinates coords, EArmyPtr Army){
	int i=0;
	ELocationPtr place = map.getPlaceAt(coords);
	if(10 - place->town_army->units.size() > Army->units.size()){
		for(i=0; i<Army->units.size(); i++){
			place->town_army->units.push_back(Army->units[i]);
		}
		Army->units.clear();
		map.setWalkable(ArmySelected->getCoords());
		ArmySelected.reset();
		player.armies.remove(Army);
	}
}

void GameClient::MergeArmies(coordinates coords, EArmyPtr Army){
	int i=0;
	EArmyPtr armyat = getArmyByCoords(coords);
	if(armyat->units.size() + Army->units.size() <= 10){
		for(i=0; i<Army->units.size(); i++){
			armyat->units.push_back(Army->units[i]);
		}
		Army->units.clear();
		map.setWalkable(ArmySelected->getCoords());
		ArmySelected=armyat;
		player.armies.remove(Army);
	}
}

EArmyPtr GameClient::getArmyByCoords(coordinates coords){
	EArmyPtr armyat;
	for (auto army: player.armies) {
		if (army->getCoords().x == coords.x and  army->getCoords().y == coords.y) {
			armyat = army;
			break;
		}
	}
	return armyat;
}

void GameClient::SendSetAP(coordinates coords) {

	ASetAPPtr action(new ASetAP);
	action->basecoords.x = PlaceSelected->getCoords().x;
	action->basecoords.y = PlaceSelected->getCoords().y;
	action->apcoords.x = coords.x;
	action->apcoords.y = coords.y;

	OnNetworkAction(action);
	//network.SendAction(action);
}

void GameClient::SendSetTurn(bool endturn) {

	ASetTurnPtr action(new ASetTurn);
	action->endturn = endturn;

	//OnNetworkAction(action);
	network.SendAction(action);
}

