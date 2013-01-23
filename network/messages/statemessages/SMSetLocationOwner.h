/*
 * SMSetLocationOwner.h
 *
 *  Created on: 23.01.2013
 *      Author: Meholli
 */

#ifndef SMSETLOCATIONOWNER_H_
#define SMSETLOCATIONOWNER_H_


#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <network/messages/GameStateMessage.h>
#include <gamemodel/utils/coordinates.h>

class SMSetLocationOwner: public GameStateMessage {
public:
	virtual ~SMSetLocationOwner();
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

typedef boost::shared_ptr<SMSetLocationOwner> SMSetLocationOwnerPtr;
#endif /* SMSETLOCATIONOWNER_H_ */
