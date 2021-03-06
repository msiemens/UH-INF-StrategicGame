/*
 * EBuilding.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef EBUILDING_H_
#define EBUILDING_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <gamemodel/GameEntity.h>

using namespace std;

class EBuilding: public GameEntity {
private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameEntity>(*this);
	}
};

typedef boost::shared_ptr<EBuilding> EBuildingPtr;

#endif /* EBUILDING_H_ */
