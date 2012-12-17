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
		player(1) {
	SurfMap = NULL;
	Surf_Display = NULL;
	SurfStartscreenBackground = NULL;
	this->running = true;
	SurfButtonSSStart = NULL;
	SurfButtonSSOption = NULL;
	SurfButtonSSServer = NULL;
	SurfButtonSSExit = NULL;
	SurfSlotSelected = NULL;
	SurfSelected = NULL;
	SurfMark = NULL;
	SurfVillage = NULL;
	SurfVillageMenuBackground = NULL;
	SurfSlotOwns = NULL;
	selected = "";
	markx = 0;
	marky = 0;
	EArmyPtr army1(new EArmy);
	army1->setName("ArmyOne");
	army1->setImgPath("client/gfx/entity/army.png");

	player.armies.insert(player.armies.begin(),army1);
}

GameClient::~GameClient() {
	// TODO Auto-generated destructor stub
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
	}

	OnCleanup();

	return 0;
}

int main(int argc, char* argv[]) {
	GameClient game;
	return game.OnExecute();
}

