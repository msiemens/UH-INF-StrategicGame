/*
 * SMUpdateActionsLeft.h
 *
 *  Created on: 21.01.2013
 *      Author: Meholli
 */

#ifndef SMUPDATEACTIONSLEFT_H_
#define SMUPDATEACTIONSLEFT_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameStateMessage.h>

class SMUpdateActionsLeft: public GameStateMessage {
public:
	virtual ~SMUpdateActionsLeft();
	int actions_left;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & actions_left;
	}
};

typedef boost::shared_ptr<SMUpdateActionsLeft> SMUpdateActionsLeftPtr;
#endif /* SMUPDATEACTIONSLEFT_H_ */
