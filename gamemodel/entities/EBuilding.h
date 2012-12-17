/*
 * EBuilding.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef EBUILDING_H_
#define EBUILDING_H_

#include <boost/shared_ptr.hpp>

#include <gamemodel/GameEntity.h>

class EBuilding: public GameEntity {
};

typedef boost::shared_ptr<EBuilding> EBuildingPtr;

#endif /* EBUILDING_H_ */
