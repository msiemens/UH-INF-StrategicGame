/*
 * SMUpdateArmy.h
 *
 *  Created on: 30.01.2013
 *      Author: Henrik
 */

#ifndef SMUPDATEARMY_H_
#define SMUPDATEARMY_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameStateMessage.h>

#include <gamemodel/entities/EArmy.h>

class SMUpdateArmy: public GameStateMessage {
public:
	SMUpdateArmy();
	virtual ~SMUpdateArmy();
	EArmyPtr army;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & army;
	}
};
typedef boost::shared_ptr<SMUpdateArmy> SMUpdateArmyPtr;
#endif /* SMUPDATEARMY_H_ */
