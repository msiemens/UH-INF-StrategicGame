/*
 * GameMetaMessage.h
 *
 *  Created on: 26.11.2012
 *      Author: markus
 */

#ifndef GAMEMETAMESSAGE_H_
#define GAMEMETAMESSAGE_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

class GameMetaMessage {
public:
	GameMetaMessage();
	virtual ~GameMetaMessage();

private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
	}
};

typedef boost::shared_ptr<GameMetaMessage> GameMetaMessagePtr;

#endif /* GAMEMETAMESSAGE_H_ */
