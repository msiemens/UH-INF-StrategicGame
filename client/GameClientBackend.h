/*
 * GameClientBackend.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#ifndef GAMECLIENTBACKEND_H_
#define GAMECLIENTBACKEND_H_

namespace std {

class GameClientBackend {
public:
	GameClientBackend();
	void OnPlayerAction(Player who, GameAction what);
	void OnGameStateMessage(); // NEED A UPDATE!
	virtual ~GameClientBackend();
};

} /* namespace std */
#endif /* GAMECLIENTBACKEND_H_ */
