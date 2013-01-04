/*
 * ABuild.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ABUILD_H_
#define ABUILD_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <gamemodel/GameAction.h>

#include <gamemodel/entities/ELocation.h>
#include <gamemodel/entities/EBuilding.h>

#include <gamemodel/utils/coordinates.h>

class ABuild: public GameAction {
public:
	virtual ~ABuild();

	EBuildingPtr what;
	ELocationPtr where;

private:
	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameAction>(*this);

		ar & what;
		ar & where;
	}
};

typedef boost::shared_ptr<ABuild> ABuildPtr;

#endif /* ABUILD_H_ */
