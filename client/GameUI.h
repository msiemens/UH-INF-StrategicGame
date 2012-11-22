/*
 * GameUI.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#include "client/GameClient.h"

#ifndef GAMEUI_H_
#define GAMEUI_H_

namespace std {

class GameUI: public GameClient {
public:
	GameUI();
	virtual ~GameUI();
};

} /* namespace std */
#endif /* GAMEUI_H_ */
