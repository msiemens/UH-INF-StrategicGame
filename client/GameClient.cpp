/*
 * GameClient.cpp
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#include <iostream>
#include <boost/bind.hpp>

#include <SDL/SDL.h>

#include "client/GameClient.h"

using namespace std;

GameClient::GameClient() :
	//player(),opponent(), network("localhost", 1337) {
	player(),opponent(), network("localhost", 1337) {
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
	SurfWalkable = NULL;
	SurfAssemblyPoint = NULL;
	SurfBlock = NULL;
	SurfPlace = NULL;
	SurfSelected = NULL;
	SurfMark = NULL;
	SurfVillage = NULL;
	SurfVillageMenuBackground = NULL;
	SurfArmyOptionBackground = NULL;
	SurfConnection = NULL;
	SurfSlotOwns = NULL;
	selected = "";
	markx = 0;
	marky = 0;
	camposx = -12;
	camposy = -12;
	pressedup = false;
	pressedright = false;
	presseddown = false;
	pressedleft = false;
	cap = true;
	frame = 0;

	// Initiaize the network and connect the signal handlers
	network.ConnectOnAction(boost::bind(&GameClient::OnNetworkAction, this, _1));
	network.ConnectOnMessage(boost::bind(&GameClient::OnNetworkMessage, this, _1));
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
		//Start the frame timer
		fps.start();

		while (SDL_PollEvent(&Event)) { //Eventqueue
			OnEvent(&Event);
		}

		OnLoop();
		OnRender();


		//If we want to cap the frame rate
		if( ( cap == true ) && ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) ) {
			//Sleep the remaining frame time
			SDL_Delay( ( 1000 / FRAMES_PER_SECOND ) - fps.get_ticks() );
		}
	}

	OnCleanup();
	return 0;
}

int main(int argc, char* argv[]) {
	GameClient game;
	return game.OnExecute();
}

