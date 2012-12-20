/*
 * GameClient.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

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
	START_SCREEN = 0, STARTUP_GAME, OPTIONS, INGAME , IG_VILLAGEMENU, SS_SERVER, SS_OPTION
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
	string ServerAddress;
	ClientNetwork network;
	GameClientBackend ClientBackend;

	SDL_Surface* Surf_Display;
	SDL_Surface* SurfConnection;
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
	SDL_Surface* SurfSlotOwns;

	//VillageMenu
	SDL_Surface* SurfVillageMenuBackground;

	//Zum test
	SDL_Surface* SurfVillage;

	string selected;
	GameEntity* gameentityselectedobject;
	int markx,marky;

public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right, bool Middle);
	void OnLButtonDown(int mX, int mY);
	void OnRButtonDown(int mX, int mY);
	void OnExit();
	void OnLoop();
	void OnRender();
	void OnCleanup();
	//void OnIncommingData();
};

#endif /* GAMECLIENT_H_ */
