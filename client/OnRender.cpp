#include "client/GameClient.h"
#include "SDL/SDL_image.h"

#include <iostream>
#include <cstring>

using namespace std;
void GameClient::OnRender() {
	int i = 0;
	if (GS.GET_GameState() == START_SCREEN) {

		Surf_Display = SDL_SetVideoMode(515, 352, 32,
				SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER);

		CSurface::OnDraw(Surf_Display, SurfStartscreenBackground, 0, 0);

		CSurface::OnDraw(Surf_Display, SurfButtonSSStart, 64, 287);
		CSurface::OnDraw(Surf_Display, SurfButtonSSOption, 164, 287);
		CSurface::OnDraw(Surf_Display, SurfButtonSSServer, 264, 287);
		CSurface::OnDraw(Surf_Display, SurfButtonSSExit, 364, 287);
	}

	if (GS.GET_GameState() == INGAME) {

		Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT + 40, 32,
				SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER);

		CSurface::OnDraw(Surf_Display, SurfMap, 0, 0);
		CSurface::OnDraw(Surf_Display, SurfSlotSelected, 0, 0);
		//test
		CSurface::OnDraw(Surf_Display, SurfArmy, 358, 243);

		if (this->selected != "") {
			char * buffer = new char[this->selected.length()];
			strcpy(buffer, this->selected.c_str());
			SurfSelected = CSurface::OnLoad(buffer);
			CSurface::OnDraw(Surf_Display, SurfSelected, 5, 5);
			if (this->markx != 0 and this->marky != 0) {
				CSurface::OnDraw(Surf_Display, SurfMark, this->markx,
						this->marky);
			}
		}

		for (auto army : player.armies) {
			char * path = new char[army->getImgPath().length()];
			strcpy(path,army->getImgPath().c_str());
			SurfSlotOwns = CSurface::OnLoad(path);
			CSurface::OnDraw(Surf_Display, SurfSlotOwns, 0 + (i * 40), 490);
			i++;
		}
		i = 0;
	}

	SDL_Flip(Surf_Display);
}
