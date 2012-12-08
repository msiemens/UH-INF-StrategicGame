#include "client/GameClient.h"
#include <iostream>


using namespace std;
bool GameClient::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		return true;
	}

	//startscreen solution
	if((Surf_Display = SDL_SetVideoMode(515, 352, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER)) == NULL){
		return false;
	}

	//Set the window caption
	SDL_WM_SetCaption( "Startegic Game", NULL );

//    if((Surf_Test = CSurface::OnLoad((char*)"client/gfx/tileset.bmp")) == NULL) {
//        return false;
//    }

	//StartScreen

	//load Background
    if((SurfStartscreenBackground = CSurface::OnLoad((char*)"client/gfx/gui/menu/background.bmp")) == NULL) {
        return false;
    }
    //Button SSExit
    if((SurfButtonSSExit = CSurface::OnLoad((char*)"client/gfx/gui/menu/buttons/exit_norm.bmp")) == NULL) {
        return false;
    }


	//load MapSurface
    if((SurfMap = CSurface::OnLoad((char*)"client/maps/map1.bmp")) == NULL) {
        return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}

