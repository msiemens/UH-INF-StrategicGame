/*
 * EPlace.h
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#ifndef EPLACE_H_
#define EPLACE_H_

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


	 void addBuilding(EBuilding building);
	 list<EBuilding> buildinglist;

	 EArmy positionedarmy;
};

#endif /* EPLACE_H_ */
