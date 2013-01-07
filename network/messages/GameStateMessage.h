/*
 * GameStateMessage.h
 *
 *  Created on: 26.11.2012
 *      Author: markus
 */

#ifndef GAMESTATEMESSAGE_H_
#define GAMESTATEMESSAGE_H_

#include <boost/shared_ptr.hpp>
#include <boost/serialization/access.hpp>

class GameStateMessage {
public:
	GameStateMessage();
	virtual ~GameStateMessage();
private:
	friend class boost::serialization::access;

	template<typename Archive>
	void serialize(Archive &ar, const unsigned int version) {
	}
};

typedef boost::shared_ptr<GameStateMessage> GameStateMessagePtr;

#endif /* GAMESTATEMESSAGE_H_ */
