/*
 * EPlace.h
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#ifndef EPLACE_H_
#define EPLACE_H_

#include <boost/shared_ptr.hpp>

#include <gamemodel/GameEntity.h>
#include <gamemodel/entities/EArmy.h>
#include <gamemodel/entities/EBuilding.h>
#include <list>

using namespace std;

class EPlace: public GameEntity {
public:
	EPlace();
	virtual ~EPlace();

	int inhabitans;
	int minInhabitans;


	 void addBuilding(EBuildingPtr building);
	 list<EBuildingPtr> buildinglist;

	 EArmyPtr positionedarmy;
};

typedef boost::shared_ptr<EPlace> EPlacePtr;

#endif /* EPLACE_H_ */
