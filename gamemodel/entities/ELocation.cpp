/*
 * EPlace.cpp
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#include "ELocation.h"

ELocation::ELocation() :
		m_inhabitans(0), town_army(new EArmy), owned(false), m_buildings() { 
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

boost::uuids::uuid ELocation::GetOwner(){
	return this->owner;
}

void ELocation::SetOwner(boost::uuids::uuid id){
	this->owner = id;
}
