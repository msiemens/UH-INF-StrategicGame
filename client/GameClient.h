/*
 * GameClient.h
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#ifndef GAMECLIENT_H_
#define GAMECLIENT_H_

#include <string>
#include <sstream>

#include <network/ClientNetwork.h>
#include <gamemodel/GameState.h>
#include <gamemodel/GameEntity.h>
#include <gamemodel/GameMap.h>
#include <gamemodel/Player.h>
#include <gamemodel/actions/ARecruit.h>

#include "CEvent.h"
#include "CSurface.h"
#include "Define.h"
#include "Timer.h"


using namespace std;

enum {
	START_SCREEN = 0, STARTUP_GAME, INGAME
};
enum{
	SUB_NONE = 0, IG_VILLAGEMENU,SS_SERVER,SS_OPTION, IG_ARMYOPTION, IG_MOVEARMY
};
enum{
	DIR_UP = 0, DIR_RIGHT, DIR_DOWN, DIR_LEFT
};

class GameClient  : public CEvent{
public:
	GameClient();
	virtual ~GameClient();
	int OnExecute();

private:
	bool running;

	GameState GS;
	GameState subGS;

	Player player;
	Player opponent;
	string ServerAddress;
	ClientNetwork network;
	GameMap map;
	bool onturn;

	SDL_Surface* Surf_Display;

	SDL_Surface* SurfMain;
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
	SDL_Surface* SurfArmyOptionBackground;

	//Zum test
	SDL_Surface* SurfVillage;
	SDL_Surface* SurfWalkable;
	SDL_Surface* SurfBlock;
	SDL_Surface* SurfPlace;


	string selected;
	GameEntity* gameentityselectedobject;
	ELocationPtr PlaceSelected;
	EArmyPtr ArmySelected;


	//The frames per second
	const int FRAMES_PER_SECOND = 20;
	//Keep track of the current frame
	int frame = 0;
	//Whether or not to cap the frame rate
	bool cap;
	//The frame rate regulator
	Timer fps;

	int markx,marky;
	int camposx,camposy;
	bool pressedup,pressedright,presseddown,pressedleft;

public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right, bool Middle);
	void OnLButtonDown(int mX, int mY);
	//HandleInput-Function
	void HandleStartScreenInput(int mX, int mY);
	void HandleVillageMenuInput(int mX, int mY);
	void HandleMapEntities(int mX, int mY);
	void HandleMapEditorModus(int mX, int mY);
	void HandleArmyOptionInput(int mX,int mY);
	void HandleMoveArmyInput(int mX,int mY);
	//-----
	void OnRButtonDown(int mX, int mY);
	void OnExit();
	void OnLoop();


	//Render function
	void OnRender();
	void RenderInGame();
	void RenderStartScreen();
	void ShowSelected();
	//-----

	void RecruitTroopInBuilding();
	void RecruitTroopOutside(coordinates coords);

	//incomming data
	void RecruitOutside(ARecruitPtr action);
	void RecruitInside(ARecruit* action);
	void MergeArmyIntoPlace(coordinates coords, EArmyPtr Army);
	void MergeArmies(coordinates coords, EArmyPtr Army);
	EArmyPtr getArmyByCoords(coordinates coords);

	void OnCleanup();
	void CameraOnMove(int x, int y);
	void CameraPosSet(int x, int y);


	// Network listeners
	void OnNetworkAction(GameActionPtr action);
	void OnNetworkMessage(GameStateMessagePtr message);
};

#endif /* GAMECLIENT_H_ */
