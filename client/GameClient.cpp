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
	SurfStartscreenBackground = NULL;
	SurfConnection = NULL;
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
	SurfConnection = NULL;
	SurfSlotOwns = NULL;
	gameentityselectedobject = NULL;
	selected = "";
	markx = 0;
	marky = 0;
	gameentityselectedobject = NULL;
	camposx = 200;
	camposy = 200;
	pressedup = false;
	pressedright = false;
	presseddown = false;
	pressedleft = false;

	EArmyPtr army1(new EArmy);
	army1->setName("ArmyOne");
	army1->setImgPath("client/gfx/entity/army.png");
	player.armies.insert(player.armies.begin(), army1);
	army1->setName("ArmyTwo");
	army1->setImgPath("client/gfx/entity/army.png");
	player.armies.insert(player.armies.end(), army1);

	EPlacePtr place1(new EPlace);
	place1->setImgPath("client/gfx/entity/village.png");
	coordinates coord(28, 30);
	place1->setCoords(coord);
	player.places.insert(player.places.begin(), place1);
	EPlacePtr place2(new EPlace);
	place2->setImgPath("client/gfx/entity/village.png");
	coordinates coord2(35, 25);
	place2->setCoords(coord2);
	player.places.insert(player.places.end(), place2);
}

GameClient::~GameClient() {
	// TODO Auto-generated destructor stub
}

void GameClient::CameraOnMove(int x, int y) {
	camposx += x;
	if(camposx < 0){
		camposx = 0;
	}else if(camposx > 640){
		camposx = 640;
	}
	camposy += y;
	if(camposy < 0){
		camposy = 0;
	}else if(camposy > 480){
		camposy = 480;
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

