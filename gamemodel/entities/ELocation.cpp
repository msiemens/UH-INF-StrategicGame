/*
 * EPlace.cpp
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#include "ELocation.h"

ELocation::ELocation() :
		m_inhabitans(0), town_army(new EArmy), owned(false), m_buildings(), isStartBase(false){
}

ELocation::~ELocation() {
}

void ELocation::addBuilding(EBuildingPtr building) {
	m_buildings.push_back(building);
}
coordinates ELocation::GetAssemblyPointCoords(){
	return this->assemblypoint;
}
void ELocation::SetAssemblyPointCoords(coordinates coords){
	this->assemblypoint.x = coords.x;
	this->assemblypoint.y = coords.y;
}
void ELocation::SetAssemblyPointCoord(int x, int y){
	this->assemblypoint.x = x;
	this->assemblypoint.y = y;
}


void ELocation::setStartBase(bool state) {
	isStartBase=state;
}
bool ELocation::IsStartBase() {
	return isStartBase;
}
