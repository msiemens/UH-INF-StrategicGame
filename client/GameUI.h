/*
 * GameUI.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#include "client/GameClient.h"
#include "gamemodel/GameState.h"

#ifndef GAMEUI_H_
#define GAMEUI_H_

namespace std {

class GameUI: public GameClient {
public:
	GameUI();
	virtual ~GameUI();
	void ShowGamestate(GameState GS);
	void ShowMap();
	void ShowSquads();
	void markSquad(ETroops Squad);
	void HandleMouseInput(int MousePosX, int MousePosY);
};

} /* namespace std */
#endif /* GAMEUI_H_ */
