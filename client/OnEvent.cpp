#include "client/GameClient.h"
#include <gamemodel/actions/ARecruit.h>
#include <gamemodel/entities/units/ECavalry.h>
#include <gamemodel/entities/units/EInfantry.h>
#include <gamemodel/entities/units/EPawn.h>

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
	if(mX > 11 and mY > 11 and mX < 488 and mY < 392)
	if (GS.GET_GameState() == INGAME) {
		if (map.editMode) {
			HandleMapEditorModus(mX,mY);
		} else {
			if (subGS.GET_GameState() == SUB_NONE) {
				if(player.onturn and ingame){
					HandleMapEntities(mX,mY);
				}
			}
		}

	}

	HandleInGameMenu(mX,mY);

	if(player.onturn){
		switch(subGS.GET_GameState()){
		case IG_VILLAGEMENU:
			HandleVillageMenuInput(mX,mY);
			break;
		case IG_ARMYOPTION:
			HandleArmyOptionInput(mX,mY);
			break;
		case IG_RECRUITOPTION:
			HandleRecruitMenuInput(mX,mY);
			break;
		case IG_MOVEARMY:
			HandleAttack(mX,mY);
			HandleMoveArmyInput(mX,mY);
			break;
		case IG_ASSEMBLYPOINT:
			HandleSetAssemblyPoint(mX,mY);
			break;
		}
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
			SDL_FreeSurface(SurfButtonSSStart);
			if (mX > 63 && mX < 152) {
				SurfButtonSSStart = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/start_hover.png");
			} else {
				SurfButtonSSStart = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/start_norm.png");
			}
			//Button Option
			SDL_FreeSurface(SurfButtonSSOption);
			if (mX > 163 && mX < 252) {
				SurfButtonSSOption = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/option_hover.png");
			} else {
				SurfButtonSSOption = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/option_norm.png");
			}
			//Button Server
			SDL_FreeSurface(SurfButtonSSServer);
			if (mX > 263 && mX < 352) {
				SurfButtonSSServer = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/server_hover.png");
			} else {
				SurfButtonSSServer = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/server_norm.png");
			}
			//Button Exit
			SDL_FreeSurface(SurfButtonSSExit);
			if (mX > 363 && mX < 452) {
				SurfButtonSSExit = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/exit_hover.png");
			} else {
				SurfButtonSSExit = CSurface::OnLoad(
						(char*) "client/gfx/gui/menu/buttons/exit_norm.png");
			}
		} else {
			SDL_FreeSurface(SurfButtonSSStart);
			SDL_FreeSurface(SurfButtonSSOption);
			SDL_FreeSurface(SurfButtonSSServer);
			SDL_FreeSurface(SurfButtonSSExit);
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
void GameClient::HandleInGameMenu(int mX, int mY){

	if(mY > 190 and mY < 219){
		if(mX > 522 and mX < 592){

		}
		if(mX > 602 and mX < 672){

		}
		if(mX > 682 and mX < 752){

		}
	}
	if(mY > 230 and mY < 259){
		if(mX > 522 and mX < 592){

		}
		if(mX > 602 and mX < 672){

		}
		if(mX > 682 and mX < 752){
			if(player.onturn){
				SendEndTurn();
			}
		}
	}

}

void GameClient::HandleStartScreenInput(int mX, int mY){
	if (mY > 287 && mY < 315) {
		//Button Start
		if (mX > 63 && mX < 152) {
			SetVideoModeInGame();
			SendLogIn();
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
	for (auto place : map.placeList) {
		if (mY > (place->getCoords().y * TILE_SIZE) - camposy and mY < (place->getCoords().y*TILE_SIZE) - camposy + TILE_SIZE) {
			if (mX > (place->getCoords().x * TILE_SIZE) - camposx and mX < (place->getCoords().x * TILE_SIZE) - camposx+ TILE_SIZE) {
				if(place->GetOwner() == player.getPlayerId()){
					ArmySelected.reset();
					PlaceSelected = place;

					subGS.SET_GameState(IG_VILLAGEMENU);
					somethingfound = true;
				}
				break;
			}
		}
	}

	for (auto army : player.armies) {
		if (mY > (army->getCoords().y * TILE_SIZE) - camposy and mY < (army->getCoords().y*TILE_SIZE) - camposy + TILE_SIZE) {
			if(mX > (army->getCoords().x * TILE_SIZE) - camposx and mX < (army->getCoords().x * TILE_SIZE) - camposx+ TILE_SIZE) {
				PlaceSelected.reset();
				ArmySelected = army;
				subGS.SET_GameState(IG_MOVEARMY);
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
void GameClient::HandleSetAssemblyPoint(int mX, int mY){
	int i=0;
	int i2=0;

	coordinates coordmouse(map.getClickPosX(mX + camposx),map.getClickPosY(mY + camposy));

	if (subGS.GET_GameState() == IG_ASSEMBLYPOINT) {
		if (PlaceSelected){
			for(i=0; i < 5;i++){
				for(i2=0; i2 < 5;i2++){
					coordinates coord(PlaceSelected->getCoords().x-2 + i2, PlaceSelected->getCoords().y-2 + i);
					if (coord.x == coordmouse.x and coord.y == coordmouse.y) {
						SendSetAP(coordmouse);
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
			recruitinside = true;
			subGS.SET_GameState(IG_RECRUITOPTION);
		}

		//recruit outside
		if (mY > 474 and mY < 501) {
			recruitinside = false;
			subGS.SET_GameState(IG_RECRUITOPTION);
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

void GameClient::HandleRecruitMenuInput(int mX, int mY){
	if (mX > 598 and mX < 685) {
		//Pawn
		if (mY > 435 and mY < 462) {
			EUnitPtr unit(new EPawn);
			if(recruitinside){
				SendRecruitTroopInBuilding(unit);
			}else{
				SendRecruitTroopOutside(unit);
			}
		}

		//infantry
		if (mY > 474 and mY < 501) {
			EUnitPtr unit(new EInfantry);
			if(recruitinside){
				SendRecruitTroopInBuilding(unit);
			}else{
				SendRecruitTroopOutside(unit);
			}
		}

		//cavalry
		if (mY > 511 and mY < 538) {
			EUnitPtr unit(new ECavalry);
			if(recruitinside){
				SendRecruitTroopInBuilding(unit);
			}else{
				SendRecruitTroopOutside(unit);
			}
		}
	}else{
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

void GameClient::HandleAttack(int mX,int mY){
	if(ArmySelected){
		coordinates coords(getCoordsByClick(mX,mY));
		if(getOpponentArmyByCoords(coords)){
			SendAttack(ArmySelected->getCoords(),coords);
		}
		ELocationPtr place(map.getPlaceAt(coords));
		if(place){
			if(place->GetOwner() != player.getPlayerId()){
				SendAttack(ArmySelected->getCoords(),coords);
			}
		}
	}
}
void GameClient::HandleMoveArmyInput(int mX,int mY){
	int i=0;
	bool inrange=false;

	if(ArmySelected){
		//DIR UP
		for(i=1; i <= ArmySelected->GetStepsLeft();i++){
			coordinates coord(ArmySelected->getCoords().x ,ArmySelected->getCoords().y- i);
			if (mY > (coord.y * TILE_SIZE) - camposy and mY < (coord.y*TILE_SIZE) - camposy + TILE_SIZE) {
				if (mX > (coord.x * TILE_SIZE) - camposx and mX < (coord.x * TILE_SIZE) - camposx+ TILE_SIZE) {
					if(!getOpponentArmyByCoords(coord)){
						SendMoveArmy(DIR_UP,i);
						inrange=true;
						break;
					}
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
					if(!getOpponentArmyByCoords(coord)){
						SendMoveArmy(DIR_RIGHT,i);
						inrange=true;
						break;
					}
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
					if(!getOpponentArmyByCoords(coord)){
						SendMoveArmy(DIR_DOWN,i);
						inrange=true;
						break;
					}
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
					if(!getOpponentArmyByCoords(coord)){
						SendMoveArmy(DIR_LEFT,i);
						inrange=true;
						break;
					}
				}
			}
		}
	}
	if(inrange == false){
		subGS.SET_GameState(SUB_NONE);
		HandleMapEntities(mX,mY);
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

//			for (auto army : player.armies) {
//				if (mY > (army->getCoords().y * TILE_SIZE) - camposy and mY < (army->getCoords().y*TILE_SIZE) - camposy + TILE_SIZE) {
//					if (mX > (army->getCoords().x * TILE_SIZE) - camposx and mX < (army->getCoords().x * TILE_SIZE) - camposx+ TILE_SIZE) {
//
//						PlaceSelected.reset();
//						ArmySelected = army;
//
//						subGS.SET_GameState(IG_ARMYOPTION);
//						//schleife kann verlassen werden
//						break;
//					}
//				}
//			}
		}
	}
}
