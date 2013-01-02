/*
 * GameClient.cpp
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#include <iostream>

#include <SDL/SDL.h>

#include "client/GameClient.h"

using namespace std;

GameClient::GameClient() :
		player(), network("localhost", 1337) {
	SurfMap = NULL;
	Surf_Display = NULL;
	SurfMain = NULL;
	SurfStartscreenBackground = NULL;
	SurfConnection = NULL;
	this->running = true;
	SurfButtonSSStart = NULL;
	SurfButtonSSOption = NULL;
	SurfButtonSSServer = NULL;
	SurfButtonSSExit = NULL;
	SurfSlotSelected = NULL;
	SurfTroopInArmy = NULL;
	SurfWalkable = NULL;
	SurfBlock = NULL;
	SurfPlace = NULL;
	SurfSelected = NULL;
	SurfMark = NULL;
	SurfVillage = NULL;
	SurfVillageMenuBackground = NULL;
	SurfArmyOptionBackground = NULL;
	SurfConnection = NULL;
	SurfSlotOwns = NULL;
	gameentityselectedobject = NULL;
	selected = "";
	markx = 0;
	marky = 0;
	gameentityselectedobject = NULL;
	camposx = -12;
	camposy = -12;
	pressedup = false;
	pressedright = false;
	presseddown = false;
	pressedleft = false;
}

GameClient::~GameClient() {
	// TODO Auto-generated destructor stub
}

void GameClient::CameraOnMove(int x, int y) {
	camposx += x;
	if(camposx < -12){ // -12 because of the bordersize (gfx/gui/main/main.png)
		camposx = -12;
	}else if(camposx > SurfMap->clip_rect.w - 488){
		camposx = SurfMap->clip_rect.w - 488;//297;
	}
	camposy += y;
	if(camposy < -12){
		camposy = -12;
	}else if(camposy > SurfMap->clip_rect.h - 392){
		camposy = SurfMap->clip_rect.h - 392;
	}

}
void GameClient::CameraPosSet(int x, int y) {
	camposx = x;
	camposy = y;
}

int GameClient::OnExecute() {

	if (OnInit() == false) {
		return -1;
	}

	SDL_Event Event;

	while (running) {
		while (SDL_PollEvent(&Event)) { //Eventqueue
			OnEvent(&Event);
		}
		OnLoop();
		OnRender();
		SDL_Delay(100);

	}

	OnCleanup();

	return 0;
}

int main(int argc, char* argv[]) {
	GameClient game;
	return game.OnExecute();
}

