/*
 * EPlace.h
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#ifndef EPLACE_H_
#define EPLACE_H_

#include "gamemodel/GameEntity.h"
#include "EBuilding.h"
#include <list>

using namespace std;

class EPlace: public GameEntity {
public:
	EPlace();
	virtual ~EPlace();

	int inhabitans;
	int mininhabitans;

	//list<EBuilding> buildinglist;
};

#endif /* EPLACE_H_ */
