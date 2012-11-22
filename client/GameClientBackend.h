/*
 * GameClientBackend.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#include "client/GameClient.h"

#ifndef GAMECLIENTBACKEND_H_
#define GAMECLIENTBACKEND_H_

namespace std {

class GameClientBackend: public GameClient {
public:
	GameClientBackend();
	virtual ~GameClientBackend();
};

} /* namespace std */
#endif /* GAMECLIENTBACKEND_H_ */
