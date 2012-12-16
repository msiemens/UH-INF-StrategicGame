#include "client/GameClient.h"
#include "SDL/SDL_image.h"

#include <iostream>
#include <cstring>

using namespace std;
void GameClient::OnRender() {
	if(GS.GET_GameState() == START_SCREEN){

		Surf_Display = SDL_SetVideoMode(515, 352, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER);

		CSurface::OnDraw(Surf_Display,SurfStartscreenBackground,0,0);

		CSurface::OnDraw(Surf_Display,SurfButtonSSStart,64,287);
		CSurface::OnDraw(Surf_Display,SurfButtonSSOption,164,287);
		CSurface::OnDraw(Surf_Display,SurfButtonSSServer,264,287);
		CSurface::OnDraw(Surf_Display,SurfButtonSSExit,364,287);
	}

	if(GS.GET_GameState() == INGAME){

		Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER);


		CSurface::OnDraw(Surf_Display,SurfMap,0,0);
		CSurface::OnDraw(Surf_Display,SurfSlotSelected,0,0);
		//test
		CSurface::OnDraw(Surf_Display,SurfArmy,358,243);

		if(this->selected != ""){
			char * buffer = new char[this->selected.length()];
			strcpy(buffer,this->selected.c_str());
			SurfSelected = CSurface::OnLoad(buffer);
			CSurface::OnDraw(Surf_Display,SurfSelected,5,5);
			if(this->markx != 0 and this->marky != 0){
				CSurface::OnDraw(Surf_Display,SurfMark,this->markx,this->marky);
			}
		}
	}

    SDL_Flip(Surf_Display);
}
