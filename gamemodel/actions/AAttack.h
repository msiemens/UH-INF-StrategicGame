/*
 * AAttack.h
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#ifndef AATTACK_H_
#define AATTACK_H_

#include <iostream>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

#include <gamemodel/utils/coordinates.h>
#include <gamemodel/GameAction.h>

class AAttack: public GameAction {
public:
	virtual ~AAttack();

	coordinates attacker;
	coordinates target;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameAction>(*this);

		ar & attacker;
		ar & target;
	}
};

typedef boost::shared_ptr<AAttack> AAttackPtr;

#endif /* AATTACK_H_ */
