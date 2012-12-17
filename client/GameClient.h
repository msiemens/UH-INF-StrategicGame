/*
 * GameClient.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

<<<<<<< HEAD
namespace std {

class GameClient {
public:
	GameClient();
	virtual ~GameClient();
	int main();				//Everthing starts here!
private:
	bool inGame;
	GameState GS;
	string ServerAddress;
	GameNetwork Network;
	GameClientBackend ClientBackend;
};

} /* namespace std */
=======
#include <string>

#include <network/ClientNetwork.h>
#include <client/GameClientBackend.h>
#include <gamemodel/GameState.h>
#include <gamemodel/Player.h>
#include <gamemodel/GameEntity.h>

#include "client/CEvent.h"
#include "client/CSurface.h"
#include "client/Define.h"


using namespace std;


enum {
	START_SCREEN = 0, STARTUP_GAME, OPTIONS, INGAME, SS_OPTION,SS_SERVERCONFIG
};

class GameClient  : public CEvent{
public:
	GameClient();
	virtual ~GameClient();
	int OnExecute();

private:
	bool running;

	GameState GS;

	Player player;
//	GameEntity gameentityobject;
	string ServerAddress;
	ClientNetwork Network;
	GameClientBackend ClientBackend;

	SDL_Surface* Surf_Display;

	SDL_Surface* SurfStartscreenBackground;
	SDL_Surface* SurfMap;

	SDL_Surface* SurfButtonSSStart;
	SDL_Surface* SurfButtonSSOption;
	SDL_Surface* SurfButtonSSServer;
	SDL_Surface* SurfButtonSSExit;

	//Inventory
	SDL_Surface* SurfSlotSelected;
	SDL_Surface* SurfSelected;
	SDL_Surface* SurfMark;

	//Zum test
	SDL_Surface* SurfArmy;
	string selected;
	int markx,marky;

public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right, bool Middle);
	void OnLButtonDown(int mX, int mY);
	void OnExit();
	void OnLoop();
	void OnRender();
	void OnCleanup();
};

>>>>>>> tmp/client
#endif /* GAMECLIENT_H_ */
