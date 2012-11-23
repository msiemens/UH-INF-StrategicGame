/*
 * EPlace.h
 *
 *  Created on: 23.11.2012
 *      Author: Henrik
 */

#ifndef EPLACE_H_
#define EPLACE_H_

#include <GameEntity.h>
#include "EBuilding.h"

namespace std {

class EPlace: public GameEntity {
public:
	EPlace();
	virtual ~EPlace();

	int inhabitans;
	list<EBuilding> buildinglist;
};

} /* namespace std */
#endif /* EPLACE_H_ */
