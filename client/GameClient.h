/*
 * GameClient.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include <string>

#include <network/GameNetwork.h>
#include <client/GameClientBackend.h>
#include <gamemodel/GameState.h>

#include "client/CEvent.h"
#include "client/CSurface.h"
#include "client/Define.h"
#include "client/CCamera.h"
#include "client/CArea.h"

using namespace std;

class GameClient  : public CEvent{
public:
	GameClient();
	virtual ~GameClient();
	int OnExecute();

private:
	bool Running;

	GameState GS;
	string ServerAddress;
	GameNetwork Network;
	GameClientBackend ClientBackend;

	SDL_Surface* Surf_Display;
	SDL_Surface* Surf_Test;

public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnExit();
	void OnLoop();
	void OnRender();
	void OnCleanup();
};

#endif /* GAMECLIENT_H_ */
