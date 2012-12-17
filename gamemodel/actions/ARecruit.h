/*
 * ARecruit.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ARECRUIT_H_
#define ARECRUIT_H_

#include <boost/shared_ptr.hpp>

#include <gamemodel/entities/ETroops.h>
#include <gamemodel/entities/EBuilding.h>
#include <gamemodel/entities/EPlace.h>

#include <gamemodel/GameAction.h>

class ARecruit: public GameAction {
public:
	ARecruit();
	virtual ~ARecruit();

	ETroopsPtr what;
	EPlacePtr base;
};

typedef boost::shared_ptr<ARecruit> ARecruitPtr;

#endif /* ARECRUIT_H_ */
