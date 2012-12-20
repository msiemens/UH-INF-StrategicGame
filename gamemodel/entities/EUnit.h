/*
 * ETroops.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef ETROOPS_H_
#define ETROOPS_H_

#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <gamemodel/GameEntity.h>

class EUnit: public GameEntity {
public:
	EUnit();
	virtual ~EUnit();

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameEntity>(*this);
	}

};

typedef boost::shared_ptr<EUnit> EUnitPtr;

#endif /* ETROOPS_H_ */
