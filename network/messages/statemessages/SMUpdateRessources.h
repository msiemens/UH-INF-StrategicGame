/*
 * SMUpdateRessources.h
 *
 *  Created on: 20.01.2013
 *      Author: Meholli
 */

#ifndef SMUPDATERESSOURCES_H_
#define SMUPDATERESSOURCES_H_


#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

#include <network/messages/GameStateMessage.h>

class SMUpdateRessources: public GameStateMessage {
public:
	virtual ~SMUpdateRessources();

	int gold;
	int stone;
	int wood;

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
		ar & boost::serialization::base_object<GameStateMessage>(*this);
		ar & gold;
		ar & wood;
		ar & stone;
	}
};

typedef boost::shared_ptr<SMUpdateRessources> SMUpdateRessourcesPtr;
#endif /* SMUPDATERESSOURCES_H_ */
