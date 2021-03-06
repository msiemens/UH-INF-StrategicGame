#include "client/GameClient.h"

using namespace std;
void GameClient::OnCleanup() {
	SDL_FreeSurface(Surf_Display);
	SDL_FreeSurface(SurfMap);
	SDL_FreeSurface(SurfSlotSelected);
	SDL_FreeSurface(SurfSelected);
	SDL_FreeSurface(SurfSlotOwns);
	SDL_FreeSurface(SurfMark);
	SDL_FreeSurface(SurfVillage);
	SDL_FreeSurface(SurfStartscreenBackground);
	SDL_FreeSurface(SurfButtonSSStart);
	SDL_FreeSurface(SurfButtonSSOption);
	SDL_FreeSurface(SurfButtonSSServer);
	SDL_FreeSurface(SurfButtonSSExit);
	SDL_FreeSurface(SurfVillageMenuBackground);

	SDL_Quit();
}
