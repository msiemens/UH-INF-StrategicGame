#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>

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

	if (GS.GET_GameState() == START_SCREEN or GS.GET_GameState() == SS_OPTION or GS.GET_GameState() == SS_SERVER) {
		if (mY > 287 && mY < 315) {
			//Button Start
			if (mX > 63 && mX < 152) {
				SurfButtonSSStart = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/start_hover.png");
			} else {
				SurfButtonSSStart = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/start_norm.png");
			}
			//Button Option
			if (mX > 163 && mX < 252) {
				SurfButtonSSOption = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/option_hover.png");
			} else {
				SurfButtonSSOption = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/option_norm.png");
			}
			//Button Server
			if (mX > 263 && mX < 352) {
				SurfButtonSSServer = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/server_hover.png");
			} else {
				SurfButtonSSServer = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/server_norm.png");
			}
			//Button Exit
			if (mX > 363 && mX < 452) {
				SurfButtonSSExit = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/exit_hover.png");
			} else {
				SurfButtonSSExit = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/exit_norm.png");
			}
		} else {
			//norm all buttons
			SurfButtonSSStart = CSurface::OnLoad(
					(char*) "client/gfx/gui/menu/buttons/start_norm.png"); //start button
			SurfButtonSSOption = CSurface::OnLoad(
					(char*) "client/gfx/gui/menu/buttons/option_norm.png");	//option button
			SurfButtonSSServer = CSurface::OnLoad(
					(char*) "client/gfx/gui/menu/buttons/server_norm.png");	//server button
			SurfButtonSSExit = CSurface::OnLoad(
					(char*) "client/gfx/gui/menu/buttons/exit_norm.png");// exit button
		}
	}
}

void GameClient::OnLButtonDown(int mX, int mY) {
	if (GS.GET_GameState() == START_SCREEN or GS.GET_GameState() == SS_OPTION or GS.GET_GameState() == SS_SERVER) {
		if (mY > 287 && mY < 315) {
			//Button Start
			if (mX > 63 && mX < 152) {
				GS.SET_GameState(INGAME);
			}
			//Button Option
			if (mX > 163 && mX < 252) {
				if(GS.GET_GameState() != SS_OPTION){
					GS.SET_GameState(SS_OPTION);
				}else{
					GS.SET_GameState(START_SCREEN);
				}
			}
			//Button Server
			if (mX > 263 && mX < 352) {
				if(GS.GET_GameState() != SS_SERVER){
					GS.SET_GameState(SS_SERVER);
				}else{
					GS.SET_GameState(START_SCREEN);
				}
			}
			//Button Exit
			if (mX > 363 && mX < 452) {
				OnExit();
			}
		}
	}

	if (GS.GET_GameState() == INGAME) {

		for (auto place : player.places) {
			if (mY > place->getCoords().y and mY < place->getCoords().y + 26) {
				if (mX > place->getCoords().x and mX < place->getCoords().x + 27) {

					this->selected = place->getImgPath();
					this->markx = place->getCoords().x;
					this->marky = place->getCoords().y;
					//gameentityselectedobject = place;
					//schleife kann verlassen werden
					break;
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

	if(GS.GET_GameState()== IG_VILLAGEMENU){
		//Recruit
		if(mY > 117 and mY < 144){
			if(mX > 409 and mX < 496){
				//if genug money =D
				ETroopsPtr troop1(new ETroops);
				troop1->setName("Army");
				troop1->setImgPath("client/gfx/entity/army.png");

				ARecruitPtr action(new ARecruit);
				action->what = troop1;
				network.SendAction(action);

				// player.armies.insert(player.armies.end(), army1);
			}
		}

		//Close
		if(mY > 230 and mY < 257){
			if(mX > 409 and mX < 496){
				GS.SET_GameState(INGAME);
			}
		}
	}
}


void GameClient::OnRButtonDown(int mX, int mY) {
	if (GS.GET_GameState() == INGAME) {
		for (auto place : player.places) {
			if (mY > place->getCoords().y and mY < place->getCoords().y + 26) {
				if (mX > place->getCoords().x and mX < place->getCoords().x + 27) {

					this->selected = place->getImgPath();
					this->markx = place->getCoords().x;
					this->marky = place->getCoords().y;
					GS.SET_GameState(IG_VILLAGEMENU);
					//schleife kann verlassen werden
					break;
				} else {
					this->selected = "";
					this->markx = 0;
					this->marky = 0;
				}	//X-coordinates

			}
		}
	}
}
