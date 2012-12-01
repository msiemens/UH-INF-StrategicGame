/*
 * ABuild.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ABUILD_H_
#define ABUILD_H_

#include "gamemodel/entities/EPlace.h"
#include "gamemodel/entities/EBuilding.h"

#include "gamemodel/GameAction.h"

class ABuild: public GameAction {
public:
	ABuild();
	virtual ~ABuild();

	EBuilding what;
	EPlace where;
};

#endif /* ABUILD_H_ */
