/*
 * ARecruit.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ARECRUIT_H_
#define ARECRUIT_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

#include <gamemodel/entities/ETroops.h>
#include <gamemodel/entities/EBuilding.h>
#include <gamemodel/entities/EPlace.h>

#include <gamemodel/GameAction.h>

class ARecruit: public GameAction {
public:
	virtual ~ARecruit();

	ETroopsPtr what;
	EPlacePtr base;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & what;
		// ar & base;
	}
};

typedef boost::shared_ptr<ARecruit> ARecruitPtr;

#endif /* ARECRUIT_H_ */
