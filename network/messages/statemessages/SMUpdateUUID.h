/*
 * SMUpdateUUID.h
 *
 *  Created on: 20.01.2013
 *      Author: Meholli
 */

#ifndef SMUPDATEUUID_H_
#define SMUPDATEUUID_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <boost/uuid/uuid_serialize.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <network/messages/GameStateMessage.h>

class SMUpdateUUID: public GameStateMessage {
public:
	virtual ~SMUpdateUUID();

boost::uuids::uuid id;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & id;
	}
};

typedef boost::shared_ptr<SMUpdateUUID> SMUpdateUUIDPtr;
#endif /* SMUPDATEUUID_H_ */
