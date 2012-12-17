/*
 * ABuild.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ABUILD_H_
#define ABUILD_H_

#include <boost/shared_ptr.hpp>

#include <gamemodel/utils/coordinates.h>
#include <gamemodel/entities/EPlace.h>
#include <gamemodel/entities/EBuilding.h>

#include <gamemodel/GameAction.h>

class ABuild: public GameAction {
public:
	virtual ~ABuild();

	EBuildingPtr what;
	EPlacePtr where;
};

typedef boost::shared_ptr<ABuild> ABuildPtr;

#endif /* ABUILD_H_ */
