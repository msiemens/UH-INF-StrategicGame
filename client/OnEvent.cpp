#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>

#include <iostream>
#include <list>

using namespace std;

void GameClient::OnEvent(SDL_Event* Event) {
	CEvent::OnEvent(Event);
}

void GameClient::OnExit() {
	running = false;
}

void GameClient::OnLButtonDown(int mX, int mY) {
	if (GS.GET_GameState() == START_SCREEN) {
		HandleStartScreenInput(mX, mY);
	}

	if (GS.GET_GameState() == INGAME) {
		if (map.editMode) {
			HandleMapEditorModus(mX,mY);
		} else {
			if (subGS.GET_GameState() == SUB_NONE) {
				HandleMapEntities(mX,mY);
			}
		}
	}

	if (subGS.GET_GameState() == IG_VILLAGEMENU) {
		HandleVillageMenuInput(mX,mY);
	}

	if (subGS.GET_GameState() == IG_ARMYOPTION) {
			HandleArmyOptionInput(mX,mY);
	}

	if (subGS.GET_GameState() == IG_MOVEARMY) {
			HandleMoveArmyInput(mX,mY);
	}
	if (subGS.GET_GameState() == IG_ASSEMBLYPOINT) {
			HandleSetAssemblyPoint(mX,mY);
	}

}

void GameClient::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
	case SDLK_UP:
		pressedup = true;
		break;
	case SDLK_DOWN:
		presseddown = true;
		break;
	case SDLK_LEFT:
		pressedleft = true;
		break;
	case SDLK_RIGHT:
		pressedright = true;
		break;
	case SDLK_e:
		if (map.editMode) {
			map.editMode = false;
		} else {
			map.editMode = true;
		}
		break;
	case SDLK_ESCAPE:
		if(subGS.GET_GameState()== IG_MOVEARMY){
			subGS.SET_GameState(SUB_NONE);
		}
		break;
	default:
		break;
	}
}

void GameClient::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch (sym) {
	case SDLK_UP:
		pressedup = false;
		break;
	case SDLK_DOWN:
		presseddown = false;
		break;
	case SDLK_LEFT:
		pressedleft = false;
		break;
	case SDLK_RIGHT:
		pressedright = false;
		break;

	default:
		break;
	}
}

void GameClient::OnMouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle) {

	if (GS.GET_GameState() == START_SCREEN) {
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

void GameClient::HandleStartScreenInput(int mX, int mY){
	if (mY > 287 && mY < 315) {
		//Button Start
		if (mX > 63 && mX < 152) {
			GS.SET_GameState(INGAME);
			subGS.SET_GameState(SUB_NONE);

			Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER);
			//Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_FULLSCREEN | SDL_HWSURFACE);
		}
		//Button Option
		if (mX > 163 && mX < 252) {
			if (subGS.GET_GameState() != SS_OPTION) {
				subGS.SET_GameState(SS_OPTION);
			} else {
				subGS.SET_GameState(SUB_NONE);
			}
		}
		//Button Server
		if (mX > 263 && mX < 352) {
			if (subGS.GET_GameState() != SS_SERVER) {
				subGS.SET_GameState(SS_SERVER);
			} else {
				subGS.SET_GameState(START_SCREEN);
			}
		}
		//Button Exit
		if (mX > 363 && mX < 452) {
			OnExit();
		}
	}
}

void GameClient::HandleMapEditorModus(int mX, int mY){
	coordinates coord(map.getClickPosX(mX + camposx),map.getClickPosY(mY + camposy));

	if (!map.isBlocked(coord)) {
		map.setBlocked(coord);
	} else {
		map.setWalkable(coord);
	}
}

void GameClient::HandleMapEntities(int mX, int mY){
	bool somethingfound=false;
	if(mX > 12 and mX < 488 and mY > 12 and mY < 392){
		for (auto place : map.placeList) {
			if (mY > (place->getCoords().y * TILE_SIZE) - camposy and mY < (place->getCoords().y*TILE_SIZE) - camposy + TILE_SIZE) {
				if (mX > (place->getCoords().x * TILE_SIZE) - camposx and mX < (place->getCoords().x * TILE_SIZE) - camposx+ TILE_SIZE) {
					ArmySelected.reset();
					PlaceSelected = place;

					subGS.SET_GameState(IG_VILLAGEMENU);
					somethingfound = true;
					break;
				}
			}
		}

		for (auto army : player.armies) {
			if (mY > (army->getCoords().y * TILE_SIZE) - camposy and mY < (army->getCoords().y*TILE_SIZE) - camposy + TILE_SIZE) {
				if(mX > (army->getCoords().x * TILE_SIZE) - camposx and mX < (army->getCoords().x * TILE_SIZE) - camposx+ TILE_SIZE) {
					PlaceSelected.reset();
					ArmySelected = army;
					somethingfound = true;
					break;
				}

			}
		}

		if(somethingfound == false){
			PlaceSelected.reset();
			ArmySelected.reset();
		}
	}
}
void GameClient::HandleSetAssemblyPoint(int mX, int mY){
	int i=0;
	int i2=0;

	coordinates coordmouse(map.getClickPosX(mX + camposx),map.getClickPosY(mY + camposy));

	if (subGS.GET_GameState() == IG_ASSEMBLYPOINT) {
		if (PlaceSelected){
			for(i=0; i < 5;i++){
				for(i2=0; i2 < 5;i2++){
					coordinates coord(PlaceSelected->getCoords().x-2 + i2, PlaceSelected->getCoords().y-2 + i);
					if (coord.x == coordmouse.x and coord.y == coordmouse.y) { //hoch
						PlaceSelected->SetAssemblyPointCoords(coordmouse);
						//senden.
						subGS.SET_GameState(IG_VILLAGEMENU);
					}
				}
			}
		}
	}
}

void GameClient::HandleVillageMenuInput(int mX, int mY){
	if (mX > 598 and mX < 685) {
		//Recruit
		if (mY > 435 and mY < 462) {
			RecruitTroopInBuilding();
		}

		//recruit outside
		if (mY > 474 and mY < 501) {
			coordinates coord(PlaceSelected->getCoords().x +1,PlaceSelected->getCoords().y);
			RecruitTroopOutside(coord);
		}

		//Close
		if (mY > 511 and mY < 538) {
			subGS.SET_GameState(IG_ASSEMBLYPOINT);

//			subGS.SET_GameState(SUB_NONE);
//			ArmySelected.reset();
		}
	}
	else{
		subGS.SET_GameState(SUB_NONE);
		ArmySelected.reset();
		HandleMapEntities(mX,mY);
	}
}

void GameClient::HandleArmyOptionInput(int mX,int mY){
	if(mY > (ArmySelected->getCoords().y*TILE_SIZE) - camposy + 27 and mY < ArmySelected->getCoords().y*TILE_SIZE - camposy + 54 ){
		if(mX > (ArmySelected->getCoords().x*TILE_SIZE - camposx + TILE_SIZE) and mX < (ArmySelected->getCoords().x*TILE_SIZE-camposx + 167 ) and ArmySelected->GetStepsLeft() > 0){
			subGS.SET_GameState(IG_MOVEARMY);
		}else{
			subGS.SET_GameState(SUB_NONE);
		}
	}else{
		subGS.SET_GameState(SUB_NONE);
	}
}

void GameClient::HandleMoveArmyInput(int mX,int mY){
	int i=0;
	if(ArmySelected){
		//DIR UP
		for(i=1; i <= ArmySelected->GetStepsLeft();i++){
			coordinates coord(ArmySelected->getCoords().x ,ArmySelected->getCoords().y- i);
			if (mY > (coord.y * TILE_SIZE) - camposy and mY < (coord.y*TILE_SIZE) - camposy + TILE_SIZE) {
				if (mX > (coord.x * TILE_SIZE) - camposx and mX < (coord.x * TILE_SIZE) - camposx+ TILE_SIZE) {
					if(map.isWalkable(coord) == true and map.isPlace(coord) == false and map.isArmyPositioned(coord)==false){
						map.setWalkable(ArmySelected->getCoords());
						ArmySelected->Move(DIR_UP,i);
						map.setArmy(ArmySelected->getCoords());
						if(ArmySelected->GetStepsLeft() == 0){
							subGS.SET_GameState(SUB_NONE);
						}
					}else if(map.isPlace(coord) == true){
						MergeArmyIntoPlace(coord, ArmySelected);
						subGS.SET_GameState(SUB_NONE);
					}else if(map.isArmyPositioned(coord) == true){
						MergeArmies(coord, ArmySelected);
						subGS.SET_GameState(SUB_NONE);
					}
					break;
				}
			}
		}
	}

	if(ArmySelected){
		//DIR RIGHT
		for(i=1; i <= ArmySelected->GetStepsLeft();i++){
			coordinates coord(ArmySelected->getCoords().x + i,ArmySelected->getCoords().y);
			if (mY > (coord.y * TILE_SIZE) - camposy and mY < (coord.y*TILE_SIZE) - camposy + TILE_SIZE) {
				if (mX > (coord.x * TILE_SIZE) - camposx and mX < (coord.x * TILE_SIZE) - camposx+ TILE_SIZE) {
					if(map.isWalkable(coord) == true and map.isPlace(coord) == false and map.isArmyPositioned(coord)==false){
						map.setWalkable(ArmySelected->getCoords());
						ArmySelected->Move(DIR_RIGHT,i);
						map.setArmy(ArmySelected->getCoords());
						if(ArmySelected->GetStepsLeft() == 0){
							subGS.SET_GameState(SUB_NONE);
						}
					}else if(map.isPlace(coord) == true){
						MergeArmyIntoPlace(coord, ArmySelected);
						subGS.SET_GameState(SUB_NONE);
					}else if(map.isArmyPositioned(coord) == true){
						MergeArmies(coord, ArmySelected);
						subGS.SET_GameState(SUB_NONE);
					}
					break;
				}
			}
		}
	}

	if(ArmySelected){
		//DIR DOWN
		for(i=1; i <= ArmySelected->GetStepsLeft();i++){
			coordinates coord(ArmySelected->getCoords().x,ArmySelected->getCoords().y + i);
			if (mY > (coord.y * TILE_SIZE) - camposy and mY < (coord.y*TILE_SIZE) - camposy + TILE_SIZE) {
				if (mX > (coord.x * TILE_SIZE) - camposx and mX < (coord.x * TILE_SIZE) - camposx+ TILE_SIZE) {
					if(map.isWalkable(coord) == true and map.isPlace(coord) == false and map.isArmyPositioned(coord)==false){
						map.setWalkable(ArmySelected->getCoords());
						ArmySelected->Move(DIR_DOWN,i);
						map.setArmy(ArmySelected->getCoords());
						if(ArmySelected->GetStepsLeft() == 0){
							subGS.SET_GameState(SUB_NONE);
						}
					}else if(map.isPlace(coord) == true){
						MergeArmyIntoPlace(coord, ArmySelected);
						subGS.SET_GameState(SUB_NONE);
					}else if(map.isArmyPositioned(coord) == true){
						MergeArmies(coord, ArmySelected);
						subGS.SET_GameState(SUB_NONE);
					}
					break;
				}
			}
		}

	}

	if(ArmySelected){
		//DIR LEFT
		for(i=1; i <= ArmySelected->GetStepsLeft();i++){
			coordinates coord(ArmySelected->getCoords().x - i,ArmySelected->getCoords().y);
			if (mY > (coord.y * TILE_SIZE) - camposy and mY < (coord.y*TILE_SIZE) - camposy + TILE_SIZE) {
				if (mX > (coord.x * TILE_SIZE) - camposx and mX < (coord.x * TILE_SIZE) - camposx+ TILE_SIZE) {
					if(map.isWalkable(coord) == true and map.isPlace(coord) == false and map.isArmyPositioned(coord)==false){
						map.setWalkable(ArmySelected->getCoords());
						ArmySelected->Move(DIR_LEFT,i);
						map.setArmy(ArmySelected->getCoords());
						if(ArmySelected->GetStepsLeft() == 0){
							subGS.SET_GameState(SUB_NONE);
						}
					}else if(map.isPlace(coord) == true){
						MergeArmyIntoPlace(coord, ArmySelected);
						subGS.SET_GameState(SUB_NONE);
					}else if(map.isArmyPositioned(coord) == true){
						MergeArmies(coord, ArmySelected);
						subGS.SET_GameState(SUB_NONE);
					}
					break;
				}
			}
		}
	}

}

void GameClient::OnRButtonDown(int mX, int mY) {
	if (GS.GET_GameState() == INGAME and subGS.GET_GameState() == SUB_NONE) {
		if(mX > 12 and mX < 488 and mY > 12 and mY < 392){
			if (map.editMode) {
				//Copy print to save the map
				map.printMapStatus();
			}
//			for (auto place : map.placeList) {
//				if (mY > (place->getCoords().y * TILE_SIZE) - camposy and mY < (place->getCoords().y*TILE_SIZE) - camposy + TILE_SIZE) {
//					if (mX > (place->getCoords().x * TILE_SIZE) - camposx and mX < (place->getCoords().x * TILE_SIZE) - camposx+ TILE_SIZE) {
//
//						ArmySelected.reset();
//						PlaceSelected = place;
//
//						subGS.SET_GameState(IG_VILLAGEMENU);
//						//schleife kann verlassen werden
//						break;
//					}
//				}
//			}

			for (auto army : player.armies) {
				if (mY > (army->getCoords().y * TILE_SIZE) - camposy and mY < (army->getCoords().y*TILE_SIZE) - camposy + TILE_SIZE) {
					if (mX > (army->getCoords().x * TILE_SIZE) - camposx and mX < (army->getCoords().x * TILE_SIZE) - camposx+ TILE_SIZE) {

						PlaceSelected.reset();
						ArmySelected = army;

						subGS.SET_GameState(IG_ARMYOPTION);
						//schleife kann verlassen werden
						break;
					}
				}
			}
		}
	}
}
