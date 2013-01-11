#include "client/GameClient.h"

#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/actions/ASetAP.h>

#include <iostream>
#include <list>

using namespace std;

void GameClient::RecruitTroopInBuilding() {
	EUnitPtr troop1(new EUnit);
	troop1->setImgPath("client/gfx/entity/army.png");
	troop1->setIconPath("client/gfx/entity/icons/army.png");

	ARecruitPtr action(new ARecruit);
	action->what = troop1;
	action->base = PlaceSelected;
	action->inside = true;
	network.SendAction(action);
}

void GameClient::RecruitTroopOutside(coordinates coords) {
	EUnitPtr troop1(new EUnit);
	troop1->setImgPath("client/gfx/entity/army.png");
	troop1->setIconPath("client/gfx/entity/icons/army.png");


	ARecruitPtr action(new ARecruit);
	action->what = troop1;
	action->base = PlaceSelected;
	action->inside = false;
	network.SendAction(action);
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
	action->ap_x = coords.x;
	action->ap_y = coords.y;

	network.SendAction(action);
}
