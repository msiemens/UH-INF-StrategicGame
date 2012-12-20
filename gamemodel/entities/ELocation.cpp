/*
 * EPlace.cpp
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#include "ELocation.h"

ELocation::ELocation() :
		m_inhabitans(0) {
}

ELocation::~ELocation() {
}

void ELocation::addBuilding(EBuildingPtr building) {
	m_buildings.push_back(building);
}
