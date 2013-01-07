#include "client/GameClient.h"
#include <iostream>

using namespace std;
bool GameClient::OnInit() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return true;
	}

	//startscreen solution
	if ((Surf_Display = SDL_SetVideoMode(515, 352, 32,
			SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER)) == NULL) {
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption("Startegic Game", NULL);

	//StartScreen

	//load Background
	if ((SurfStartscreenBackground = CSurface::OnLoad(
			(char*) "client/gfx/gui/menu/background.png")) == NULL) {
		return false;
	}
	//Button SSExit
	if ((SurfButtonSSExit = CSurface::OnLoad(
			(char*) "client/gfx/gui/menu/buttons/exit_norm.png")) == NULL) {
		return false;
	}
	//ingame
	//load mainbrackground
	if ((SurfMain = CSurface::OnLoad((char*) "client/gfx/gui/main/main.png")) == NULL) {
		return false;
	}

	//load MapSurface
	if ((SurfMap = CSurface::OnLoad((char*) "client/maps/map3.png")) == NULL) {
		return false;
	}

	//load SlotSelected
	if ((SurfSlotSelected = CSurface::OnLoad(
			(char*) "client/gfx/gui/inventory/itemslot.png")) == NULL) {
		return false;
	}

	//load village
	if ((SurfVillage = CSurface::OnLoad((char*) "client/gfx/entity/village.png"))
			== NULL) {
		return false;
	}

	if ((SurfVillageMenuBackground = CSurface::OnLoad(
			(char*) "client/gfx/gui/menu/villagemenubg.png")) == NULL) {
		return false;
	}
	if ((SurfArmyOptionBackground = CSurface::OnLoad(
			(char*) "client/gfx/gui/menu/armyoptions.png")) == NULL) {
		return false;
	}

	if ((SurfMark = CSurface::OnLoad((char*) "client/gfx/entity/mark.png"))
			== NULL) {
		return false;
	}
	if ((SurfWalkable = CSurface::OnLoad((char*) "client/gfx/entity/walkable.png"))
			== NULL) {
		return false;
	}
	if ((SurfBlock= CSurface::OnLoad((char*) "client/gfx/entity/block.png"))
			== NULL) {
		return false;
	}
	if ((SurfPlace = CSurface::OnLoad((char*) "client/gfx/entity/entity.png"))
			== NULL) {
		return false;
	}

	if (/*network.IsConnected() ==*/ true) {
		if ((SurfConnection = CSurface::OnLoad(
				(char*) "client/gfx/gui/main/serveronline.png")) == NULL) {
			return false;
		}
	} else {
		if ((SurfConnection = CSurface::OnLoad(
				(char*) "client/gfx/gui/main/serveroffline.png")) == NULL) {
			return false;
		}
	}

	if (SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY,
			SDL_DEFAULT_REPEAT_INTERVAL) == -1) {
		cout << "SDL_EnableKeyRepeat failed. OnInit.cpp /72";
		return false;
	}

	return true;
}

