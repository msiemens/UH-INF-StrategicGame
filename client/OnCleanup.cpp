#include "client/GameClient.h"

using namespace std;
void GameClient::OnCleanup() {
	SDL_FreeSurface(Surf_Test);
	SDL_FreeSurface(Surf_Display);
	CArea::AreaControl.OnCleanup();
	SDL_Quit();
}
