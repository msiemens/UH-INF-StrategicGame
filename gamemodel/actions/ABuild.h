/*
 * ABuild.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ABUILD_H_
#define ABUILD_H_

#include <gamemodel/utils/coordinates.h>
#include <gamemodel/entities/EBuilding.h>

#include <gamemodel/GameAction.h>

class ABuild: public GameAction {
public:
	ABuild();
	virtual ~ABuild();

	EBuilding what;
	coordinates where;
};

#endif /* ABUILD_H_ */
