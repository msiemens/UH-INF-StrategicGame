/*
 * EPlace.cpp
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#include "gamemodel/entities/EPlace.h"

EPlace::EPlace() {
	// TODO Auto-generated constructor stub
	inhabitans=0;
	minInhabitans=0;
}

EPlace::~EPlace() {
	// TODO Auto-generated destructor stub
}

 void EPlace::addBuilding(EBuildingPtr building){
	 buildinglist.insert(buildinglist.begin(),building);
 }


