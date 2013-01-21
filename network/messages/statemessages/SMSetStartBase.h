/*
 * SMSetStartBase.h
 *
 *  Created on: 21.01.2013
 *      Author: Meholli
 */

#ifndef SMSETSTARTBASE_H_
#define SMSETSTARTBASE_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameStateMessage.h>
#include <gamemodel/utils/coordinates.h>


class SMSetStartBase: public GameStateMessage {
public:
	virtual ~SMSetStartBase();

	coordinates coords;
private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & coords;
	}
};

typedef boost::shared_ptr<SMSetStartBase> SMSetStartBasePtr;
#endif /* SMSETSTARTBASE_H_ */
