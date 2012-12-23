#include "client/GameClient.h"
#include "SDL/SDL_image.h"

#include <iostream>
#include <cstring>

using namespace std;
void GameClient::OnRender() {
	int i = 0;
	if (GS.GET_GameState() == START_SCREEN or GS.GET_GameState() == SS_SERVER
			or GS.GET_GameState() == SS_OPTION) {

		Surf_Display = SDL_SetVideoMode(515, 352, 32,
				SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER);

		CSurface::OnDraw(Surf_Display, SurfStartscreenBackground, 0, 0);

		CSurface::OnDraw(Surf_Display, SurfButtonSSStart, 64, 287);
		CSurface::OnDraw(Surf_Display, SurfButtonSSOption, 164, 287);
		CSurface::OnDraw(Surf_Display, SurfButtonSSServer, 264, 287);
		CSurface::OnDraw(Surf_Display, SurfButtonSSExit, 364, 287);

		if (GS.GET_GameState() == SS_SERVER) {
			CSurface::OnDraw(Surf_Display, SurfConnection, 50, 50);
		}
	}

	if (GS.GET_GameState() == INGAME or GS.GET_GameState() == IG_VILLAGEMENU) {

		Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32,
				SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER);

		CSurface::OnDraw(Surf_Display, SurfMap, 0, 0, camposx, camposy, 640, 480);
		CSurface::OnDraw(Surf_Display, SurfSlotSelected, 0, 0);

		//show villages
		for (auto place : player.places) {
			char * path = new char[place->getImgPath().length()];
			strcpy(path, place->getImgPath().c_str());
			SurfVillage = CSurface::OnLoad(path);

			CSurface::OnDraw(Surf_Display, SurfVillage, (place->getCoords().x * TILE_SIZE) - camposx,
					(place->getCoords().y * 20)-camposy);
		}

		if (this->selected != "") {
			char * buffer = new char[this->selected.length()];
			strcpy(buffer, this->selected.c_str());
			SurfSelected = CSurface::OnLoad(buffer);
			CSurface::OnDraw(Surf_Display, SurfSelected, 5, 5);
			if (this->markx != 0 and this->marky != 0) {
				CSurface::OnDraw(Surf_Display, SurfMark, this->markx * TILE_SIZE - camposx,
						this->marky * TILE_SIZE - camposy);
			}
		}
		if (GS.GET_GameState() == IG_VILLAGEMENU) {
			CSurface::OnDraw(Surf_Display, SurfVillageMenuBackground, 50, 50);

			//show armies
			for (auto army : player.armies) {
				char * path = new char[army->getImgPath().length()];
				strcpy(path, army->getImgPath().c_str());
				SurfSlotOwns = CSurface::OnLoad(path);
				CSurface::OnDraw(Surf_Display, SurfSlotOwns, 108 + (i * 40),
						278);
				i++;
			}
			i = 0;
		}

	}

	SDL_Flip(Surf_Display);
}
