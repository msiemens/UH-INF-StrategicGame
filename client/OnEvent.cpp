#include "client/GameClient.h"
#include <iostream>

using namespace std;
void GameClient::OnEvent(SDL_Event* Event) {
	CEvent::OnEvent(Event);
}

void GameClient::OnExit() {
	running = false;
}

void GameClient::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
	case SDLK_UP:

		GS.SET_GameState(INGAME);
		// CCamera::CameraControl.OnMove(0, 5);
		break;
	case SDLK_DOWN:
		GS.SET_GameState(START_SCREEN);
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
void GameClient::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,
		bool Right, bool Middle) {

	if (GS.GET_GameState() == START_SCREEN) {
		if (mY > 287 && mY < 315) {
			//Button Start
			if (mX > 63 && mX < 152) {
				SurfButtonSSStart = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/start_hover.bmp");
			} else {
				SurfButtonSSStart = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/start_norm.bmp");
			}
			//Button Option
			if (mX > 163 && mX < 252) {
				SurfButtonSSOption = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/option_hover.bmp");
			} else {
				SurfButtonSSOption = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/option_norm.bmp");
			}
			//Button Server
			if (mX > 263 && mX < 352) {
				SurfButtonSSServer = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/server_hover.bmp");
			} else {
				SurfButtonSSServer = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/server_norm.bmp");
			}
			//Button Exit
			if (mX > 363 && mX < 452) {
				SurfButtonSSExit = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/exit_hover.bmp");
			} else {
				SurfButtonSSExit = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/exit_norm.bmp");
			}
		} else {
			//norm all buttons
			SurfButtonSSStart = CSurface::OnLoad(
					(char*) "client/gfx/gui/menu/buttons/start_norm.bmp"); //start button
			SurfButtonSSOption = CSurface::OnLoad(
					(char*) "client/gfx/gui/menu/buttons/option_norm.bmp");	//option button
			SurfButtonSSServer = CSurface::OnLoad(
					(char*) "client/gfx/gui/menu/buttons/server_norm.bmp");	//server button
			SurfButtonSSExit = CSurface::OnLoad(
					(char*) "client/gfx/gui/menu/buttons/exit_norm.bmp");// exit button
		}
	}
}
void GameClient::OnLButtonDown(int mX, int mY) {
	if (GS.GET_GameState() == START_SCREEN) {
		if (mY > 287 && mY < 315) {
			//Button Start
			if (mX > 63 && mX < 152) {
				GS.SET_GameState(INGAME);
			}
			//Button Option
			if (mX > 163 && mX < 252) {
				GS.SET_GameState(INGAME);
			}
			//Button Server
			if (mX > 263 && mX < 352) {
				GS.SET_GameState(INGAME);
			}
			//Button Exit
			if (mX > 363 && mX < 452) {
				OnExit();
			}
		}
	}

	if (GS.GET_GameState() == INGAME) {

		if (mY > 0 and mY < 30) {
			if (mX > 0 and mX < 30) {
				EArmyPtr army1(new EArmy);
				army1->setName("Army");
				army1->setImgPath("client/gfx/entity/army.png");
				player.armies.insert(player.armies.end(), army1);
			}
		}

		if (mY > (int) SurfVillage->clip_rect.y
				and mY < (int) (SurfVillage->clip_rect.y + SurfVillage->clip_rect.h)) {
			if (mX > (int) SurfVillage->clip_rect.x
					and mX
							< (int) (SurfVillage->clip_rect.x + SurfVillage->clip_rect.w)) {

				this->selected = "client/gfx/entity/village.png";
				this->markx = (int) SurfVillage->clip_rect.x;
				this->marky = (int) SurfVillage->clip_rect.y;
				GS.SET_GameState(IG_VILLAGEMENU);
			} else {
				this->selected = "";
				this->markx = 0;
				this->marky = 0;
			}	//X-coordinates

		} else {
			this->selected = "";
			this->markx = 0;
			this->marky = 0;
		}	//Y-coordinates
	}
}
