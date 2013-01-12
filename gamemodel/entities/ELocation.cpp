/*
 * EPlace.cpp
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#include "ELocation.h"

ELocation::ELocation() :
		m_inhabitans(0), town_army(new EArmy), m_buildings() {
}

ELocation::~ELocation() {
}

void ELocation::addBuilding(EBuildingPtr building) {
	m_buildings.push_back(building);
}
