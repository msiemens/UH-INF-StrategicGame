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

GameClient::GameClient() {
	Surf_Test = NULL;
	Surf_Display = NULL;
	this->Running = true;
}

GameClient::~GameClient() {
	// TODO Auto-generated destructor stub
}

int GameClient::OnExecute() {
	if (OnInit() == false) {
		return -1;
	}

	SDL_Event Event;

	while (Running) {
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

