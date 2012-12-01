#include "client/GameClient.h"
#include <iostream>


using namespace std;
bool GameClient::OnInit() {
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
		return true;
	}

	if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER)) == NULL){
		return false;
	}

//    if((Surf_Test = CSurface::OnLoad((char*)"client/gfx/tileset.bmp")) == NULL) {
//        return false;
//    }

    //if(CArea::AreaControl.OnLoad((char*)"client/maps/1.area") == false) {
    //    return false;
    //}

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}

