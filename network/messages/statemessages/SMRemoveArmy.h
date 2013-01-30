/*
 * SMRemoveArmy.h
 *
 *  Created on: 30.01.2013
 *      Author: Meholli
 */

#ifndef SMREMOVEARMY_H_
#define SMREMOVEARMY_H_

#include <network/messages/GameStateMessage.h>

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <gamemodel/utils/coordinates.h>

class SMRemoveArmy: public GameStateMessage {
public:
	virtual ~SMRemoveArmy();
	coordinates coords;
	boost::uuids::uuid owner;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & coords;
		ar & owner;
	}
};

typedef boost::shared_ptr<SMRemoveArmy> SMRemoveArmyPtr;
#endif /* SMREMOVEARMY_H_ */
