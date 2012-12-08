#include "client/GameClient.h"

using namespace std;
void GameClient::OnCleanup() {
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(SurfMap);
	SDL_FreeSurface(SurfStartscreenBackground);
	SDL_FreeSurface(SurfButtonSSStart);
	SDL_FreeSurface(SurfButtonSSOption);
	SDL_FreeSurface(SurfButtonSSServer);
	SDL_FreeSurface(SurfButtonSSExit);


	SDL_Quit();
}
