#include "client/GameClient.h"

using namespace std;
void GameClient::OnEvent(SDL_Event* Event) {
	CEvent::OnEvent(Event);
}

void GameClient::OnExit() {
	Running = false;
}

void GameClient::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
	case SDLK_UP:
		// CCamera::CameraControl.OnMove(0, 5);
		break;
	case SDLK_DOWN:
		// CCamera::CameraControl.OnMove(0, -5);
		break;
	case SDLK_LEFT:
		// CCamera::CameraControl.OnMove(5, 0);
		break;
	case SDLK_RIGHT:
		// CCamera::CameraControl.OnMove(-5, 0);
		break;

	default:
		break;
	}
}
