/*
 * GameMetaMessage.h
 *
 *  Created on: 26.11.2012
 *      Author: markus
 */

#ifndef GAMEMETAMESSAGE_H_
#define GAMEMETAMESSAGE_H_

#include <boost/shared_ptr.hpp>

class GameMetaMessage {
public:
	GameMetaMessage();
	virtual ~GameMetaMessage();
};

typedef boost::shared_ptr<GameMetaMessage> GameMetaMessagePtr;

#endif /* GAMEMETAMESSAGE_H_ */
