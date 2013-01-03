#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>

#include <iostream>
#include <list>

using namespace std;

void GameClient::RecruitTroopInBuilding() {
	//if genug money =D
	ETroopsPtr troop1(new ETroops);
	troop1->setName("Army");
	troop1->setImgPath("client/gfx/entity/army.png");
	troop1->setIconPath("client/gfx/entity/icons/army.png");

	if (PlaceSelected->positionedarmy->troops.size() < 10) {
		PlaceSelected->positionedarmy->addTroop(troop1);
	}

	ARecruitPtr action(new ARecruit);
	action->what = troop1;
	network.SendAction(action);
}

void GameClient::RecruitTroopOutside(coordinates coords) {
	//if genug money =D
	ETroopsPtr troop1(new ETroops);
	troop1->setName("Troop");
	troop1->setImgPath("client/gfx/entity/army.png");
	troop1->setIconPath("client/gfx/entity/icons/army.png");

	if (map.isArmyPositioned(coords)) {
		for (auto army : player.armies){
			if (army->getCoords().x == coords.x
					and army->getCoords().y == coords.y) {
				army->addTroop(troop1);
			}
		}
	} else {
		EArmyPtr army(new EArmy);
		army->setImgPath("client/gfx/entity/army.png");
		army->setName("Army");
		army->addTroop(troop1);
		army->setStep(3);
		army->setCoords(coords);
		player.armies.insert(player.armies.end(), army);
		map.setArmy(coords);
	}
}

void GameClient::MergeArmyIntoPlace(coordinates coords, EArmyPtr Army){
	int i=0;
	EPlacePtr place = map.getPlaceAt(coords);
	if(10 - place->positionedarmy->troops.size() > Army->troops.size()){
		for(i=0; i<Army->troops.size(); i++){
			place->positionedarmy->troops.push_back(Army->troops[i]);
		}
		Army->troops.clear();
		map.setWalkable(ArmySelected->getCoords());
		ArmySelected.reset();
		player.armies.remove(Army);
	}
}
void GameClient::MergeArmies(coordinates coords, EArmyPtr Army){
	int i=0;
	EArmyPtr armyat = getArmyByCoords(coords);
	if(armyat->troops.size() + Army->troops.size() <= 10){
		for(i=0; i<Army->troops.size(); i++){
			armyat->troops.push_back(Army->troops[i]);
		}
		Army->troops.clear();
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
