/*
 * SMUpdateLocationArmy.h
 *
 *  Created on: 30.01.2013
 *      Author: Meholli
 */

#ifndef SMUPDATELOCATIONARMY_H_
#define SMUPDATELOCATIONARMY_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameStateMessage.h>
#include <gamemodel/utils/coordinates.h>

class SMUpdateLocationArmy: public GameStateMessage {
public:
	virtual ~SMUpdateLocationArmy();
	EArmyPtr army;
	coordinates coords;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & army;
		ar & coords;
	}
};
typedef boost::shared_ptr<SMUpdateLocationArmy> SMUpdateLocationArmyPtr;
#endif /* SMUPDATELOCATIONARMY_H_ */
