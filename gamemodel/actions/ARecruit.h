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
#include <boost/serialization/base_object.hpp>

#include <gamemodel/GameAction.h>

#include <gamemodel/entities/EUnit.h>
#include <gamemodel/entities/ELocation.h>
#include <gamemodel/utils/coordinates.h>

class ARecruit: public GameAction {
public:
	virtual ~ARecruit();

	EUnitPtr what;
	ELocationPtr base;
	bool inside;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameAction>(*this);

		ar & what;
		ar & base;
		ar & inside;
	}
};

typedef boost::shared_ptr<ARecruit> ARecruitPtr;

#endif /* ARECRUIT_H_ */
