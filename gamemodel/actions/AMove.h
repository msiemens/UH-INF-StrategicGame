/*
 * AMove.h
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#ifndef AMOVE_H_
#define AMOVE_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <gamemodel/GameEntity.h>
#include <gamemodel/GameAction.h>

#include <gamemodel/utils/coordinates.h>

class AMove: public GameAction {
public:
	virtual ~AMove();

	coordinates to;
	GameEntityPtr what;
	int count;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameAction>(*this);

		ar & what;
		ar & to;
		ar & count;
	}
};

typedef boost::shared_ptr<AMove> AMovePtr;

#endif /* AMOVE_H_ */
