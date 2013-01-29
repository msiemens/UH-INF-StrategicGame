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
#include <gamemodel/actions/AMove.h>
#include <gamemodel/actions/ASetAP.h>
#include <gamemodel/actions/ASetTurn.h>
#include <gamemodel/actions/ALogIn.h>

#include <SDL/SDL_ttf.h>

#include "CEvent.h"
#include "CSurface.h"
#include "Define.h"
#include "Timer.h"


using namespace std;

enum {
	START_SCREEN = 0, STARTUP_GAME, INGAME
};
enum{
	SUB_NONE = 0, IG_VILLAGEMENU,SS_SERVER,SS_OPTION, IG_ARMYOPTION, IG_MOVEARMY, IG_ASSEMBLYPOINT, IG_RECRUITOPTION
};
enum{
	DIR_UP = 0, DIR_RIGHT, DIR_DOWN, DIR_LEFT
};

class GameClient  : public CEvent{
public:
	GameClient();
	GameClient(char* hostname, char* port);
	virtual ~GameClient();
	int OnExecute();

private:
	void init();

	bool running;
	bool ingame;

	GameState GS;
	GameState subGS;

	Player player;
	Player opponent;
	string ServerAddress;
	ClientNetwork network;
	GameMap map;

	SDL_Surface* Surf_Display;

	SDL_Surface* SurfMain;
	SDL_Surface* SurfConnection;
	SDL_Surface* SurfStartscreenBackground;
	SDL_Surface* SurfMap;

	//show Turn
	SDL_Surface* SurfOnTurn;
	SDL_Surface* SurfOffTurn;

	//Startscreen-Buttons
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
	SDL_Surface* SurfAssemblyPoint;

	//recruit Menu
	SDL_Surface* SurfRecruitMenuBackground;

	//Zum test
	SDL_Surface* SurfVillage;
	SDL_Surface* SurfWalkable;
	SDL_Surface* SurfBlock;
	SDL_Surface* SurfPlace;


	string selected;
	ELocationPtr PlaceSelected;
	EArmyPtr ArmySelected;

	bool recruitinside;
	//================================
	//===========TTF VARS=============
	//================================

	//The font that's going to be used
	TTF_Font *font;
	TTF_Font *font_amount;
	 //The color of the font
	SDL_Color textColor;
	//used to show the message
	SDL_Surface* message;
	SDL_Surface* amount;
	SDL_Surface* gold;
	SDL_Surface* wood;
	SDL_Surface* stone;
	SDL_Surface* actions_left;

	//================================
	//========END TTF VARS============
	//================================



	//The frames per second
	int FRAMES_PER_SECOND;
	//Keep track of the current frame
	int frame;
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
	void OnRButtonDown(int mX, int mY);
	void OnExit();
	void OnLoop();

//======================================
//============ HandleInput =============
//======================================
	void HandleStartScreenInput(int mX, int mY);
	void HandleVillageMenuInput(int mX, int mY);
	void HandleRecruitMenuInput(int mX, int mY);
	void HandleMapEntities(int mX, int mY);
	void HandleInGameMenu(int mX, int mY);
	void HandleMapEditorModus(int mX, int mY);
	void HandleArmyOptionInput(int mX,int mY);
	void HandleMoveArmyInput(int mX,int mY);
	void HandleAttack(int mX,int mY);
	void HandleSetAssemblyPoint(int mX,int mY);

//======================================
//============= Render =================
//======================================
	void SetVideoModeInGame();
	void OnRender();
	void RenderInGame();
	void RenderStartScreen();
	void RenderRessources();
	void ShowSelected();

//======================================
//=============== Get ==================
//======================================
	EArmyPtr getArmyByCoords(coordinates coords);
	EArmyPtr getOpponentArmyByCoords(coordinates coords);
	coordinates getCoordsByClick(int mX,int mY);
	char* getCharArrayByInt(int value);
	char* getCharArrayByString(string text);


//======================================
//============= Network ================
//======================================
	//incomming data
	void RecruitOutside(ARecruit* action);
	void RecruitInside(ARecruit* action);
	void MergeArmyIntoPlace(coordinates coords, EArmyPtr Army);
	void MergeArmies(coordinates coords, EArmyPtr Army);

	void OnCleanup();
	void CameraOnMove(int x, int y);
	void CameraPosSet(int x, int y);

	//send functions
	void SendLogIn();
	void SendMoveArmy(int dir, int size);
	void SendAttack(coordinates attacker, coordinates target);
	void SendSetAP(coordinates coords);
	void SendEndTurn();
	void SendRecruitTroopInBuilding(EUnitPtr unit);
	void SendRecruitTroopOutside(EUnitPtr unit);

	//receive functions
	void ReceiveLogIn(ALogIn* login);
	void ReceiveMoveArmy(AMove* move);
	void ReceiveSetAP(ELocationPtr place, coordinates coords);
	void ReceiveSetTurn(bool endturn);

	void OnNextTurn();
	// Network listeners
	void OnNetworkAction(GameActionPtr action);
	void OnNetworkMessage(GameStateMessagePtr message);
};

#endif /* GAMECLIENT_H_ */
