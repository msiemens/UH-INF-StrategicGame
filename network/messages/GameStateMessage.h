/*
 * GameStateMessage.h
 *
 *  Created on: 26.11.2012
 *      Author: markus
 */

#ifndef GAMESTATEMESSAGE_H_
#define GAMESTATEMESSAGE_H_

#include <boost/shared_ptr.hpp>

class GameStateMessage {
public:
	GameStateMessage();
	virtual ~GameStateMessage();
};

typedef boost::shared_ptr<GameStateMessage> GameStateMessagePtr;

#endif /* GAMESTATEMESSAGE_H_ */
