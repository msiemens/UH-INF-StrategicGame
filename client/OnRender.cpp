#include "client/GameClient.h"
#include "SDL/SDL_image.h"

#include <iostream>
#include <cstring>

using namespace std;

void GameClient::RenderStartScreen() {
	Surf_Display = SDL_SetVideoMode(515, 352, 32,
			SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER);

	CSurface::OnDraw(Surf_Display, SurfStartscreenBackground, 0, 0);

	CSurface::OnDraw(Surf_Display, SurfButtonSSStart, 64, 287);
	CSurface::OnDraw(Surf_Display, SurfButtonSSOption, 164, 287);
	CSurface::OnDraw(Surf_Display, SurfButtonSSServer, 264, 287);
	CSurface::OnDraw(Surf_Display, SurfButtonSSExit, 364, 287);

	if (subGS.GET_GameState() == SS_SERVER) {
		CSurface::OnDraw(Surf_Display, SurfConnection, 50, 50);
	}
}

void GameClient::ShowSelected() {
	int i=0;

	if (PlaceSelected) {
		char * buffer = new char[PlaceSelected->getIconPath().length()];
		strcpy(buffer, PlaceSelected->getIconPath().c_str());
		SurfSelected = CSurface::OnLoad(buffer);
		CSurface::OnDraw(Surf_Display, SurfSelected, 608, 347);

		if (PlaceSelected->getCoords().x != 0 and PlaceSelected->getCoords().y != 0) {
			int mX = PlaceSelected->getCoords().x * TILE_SIZE - camposx;
			int mY = PlaceSelected->getCoords().y * TILE_SIZE - camposy;
			if(mX > 12 and mX < 488 and mY > 12 and mY < 392){
				CSurface::OnDraw(Surf_Display, SurfMark,
					PlaceSelected->getCoords().x * TILE_SIZE - camposx,
					PlaceSelected->getCoords().y * TILE_SIZE - camposy);
			}
		}

		if (PlaceSelected->GetAssemblyPointCoords().x != 0 and PlaceSelected->GetAssemblyPointCoords().y != 0) {
			int mX = PlaceSelected->GetAssemblyPointCoords().x * TILE_SIZE - camposx;
			int mY = PlaceSelected->GetAssemblyPointCoords().y * TILE_SIZE - camposy;
			if(mX > 12 and mX < 488 and mY > 12 and mY < 392){
				CSurface::OnDraw(Surf_Display, SurfAssemblyPoint,mX,mY);
			}
		}
	}

	if (ArmySelected) {
//		char * buffer = new char[ArmySelected->getIconPath().length()];
//		strcpy(buffer, ArmySelected->getIconPath().c_str());
		char * buffer = new char[ArmySelected->getImgPath().length()];
		strcpy(buffer, ArmySelected->getImgPath().c_str());
		SurfSelected = CSurface::OnLoad(buffer);
		CSurface::OnDraw(Surf_Display, SurfSelected, 608, 347);

		if (ArmySelected->getCoords().x != 0
				and ArmySelected->getCoords().y != 0) {
			int mX = ArmySelected->getCoords().x * TILE_SIZE - camposx;
			int mY = ArmySelected->getCoords().y * TILE_SIZE - camposy;
			if(mX > 12 and mX < 488 and mY > 12 and mY < 392){
				CSurface::OnDraw(Surf_Display, SurfMark,
					ArmySelected->getCoords().x * TILE_SIZE - camposx,
					ArmySelected->getCoords().y * TILE_SIZE - camposy);
			}
		}

		for (i = 0; i < ArmySelected->units.size(); i++) {
			char * path =
					new char[ArmySelected->units[i]->getImgPath().length()];
			strcpy(path, ArmySelected->units[i]->getImgPath().c_str());
			SurfSlotOwns = CSurface::OnLoad(path);
			CSurface::OnDraw(Surf_Display, SurfSlotOwns, 18 + (i * 40), 405);
		}

	}
}

void GameClient::RenderInGame() {
	int i = 0;
	int i2 = 0;
	int x = 0;

	CSurface::OnDraw(Surf_Display, SurfMap, 0, 0, camposx, camposy, WWIDTH,
			WHEIGHT);

	//show villages
	for (auto place : map.placeList) {
		char * path = new char[place->getImgPath().length()];
		strcpy(path, place->getImgPath().c_str());
		SurfVillage = CSurface::OnLoad(path);

		CSurface::OnDraw(Surf_Display, SurfVillage,
				(place->getCoords().x * TILE_SIZE) - camposx,
				(place->getCoords().y * 20) - camposy);
	}
	//show Troops
	for (auto army : player.armies) {
		char * path = new char[army->getImgPath().length()];
		strcpy(path, army->getImgPath().c_str());
		SurfVillage = CSurface::OnLoad(path);

		CSurface::OnDraw(Surf_Display, SurfVillage,
				(army->getCoords().x * TILE_SIZE) - camposx,
				(army->getCoords().y * 20) - camposy);
	}

	if (map.editMode) {
		for (i = 0; i < map.mapSizeY; i++) {
			for (x = 0; x < map.mapSizeX; x++) {
				coordinates coord(x, i); //i = y
				if (map.isWalkable(coord)) {
					CSurface::OnDraw(Surf_Display, SurfWalkable,
							(x * TILE_SIZE) - camposx,
							(i * TILE_SIZE) - camposy);
				}
				if (map.isPlace(coord)) {
					CSurface::OnDraw(Surf_Display, SurfWalkable,
							(x * TILE_SIZE) - camposx,
							(i * TILE_SIZE) - camposy);
				}
				if (map.isBlocked(coord)) {
					CSurface::OnDraw(Surf_Display, SurfBlock,
							(x * TILE_SIZE) - camposx,
							(i * TILE_SIZE) - camposy);
				}
			}
		}
	}

	if (subGS.GET_GameState() == IG_MOVEARMY) {
		if (ArmySelected) {
			// show moveable fields
			for (i = 1; i <= ArmySelected->GetStepsLeft(); i++) {
				coordinates coord(ArmySelected->getCoords().x + i,
						ArmySelected->getCoords().y);

				if (map.isWalkable(coord) == true
						and map.isPlace(coord) == false
						and map.isArmyPositioned(coord) == false) { //rechts lang
					CSurface::OnDraw(Surf_Display, SurfWalkable,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);
				} else if(map.isPlace(coord) == true) {
					CSurface::OnDraw(Surf_Display, SurfPlace,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);
					break; //schleife verlassen nach einem Gebäude
				}else if(map.isArmyPositioned(coord) == true){
					CSurface::OnDraw(Surf_Display, SurfBlock,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);//village zu testzwecken
					break; //schleife verlassen nach einer armee
				}else{
					break; //schleife verlassen wenn nicht begehbar
				}
			}

			for (i = 1; i <= ArmySelected->GetStepsLeft(); i++) {
				coordinates coord(ArmySelected->getCoords().x,
						ArmySelected->getCoords().y + i);
				if (map.isWalkable(coord) == true
						and map.isPlace(coord) == false
						and map.isArmyPositioned(coord) == false) { //runter
					CSurface::OnDraw(Surf_Display, SurfWalkable,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);
				} else if(map.isPlace(coord) == true) {
					CSurface::OnDraw(Surf_Display, SurfPlace,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);
					break; //schleife verlassen nach einem Gebäude
				}else if(map.isArmyPositioned(coord) == true){
					CSurface::OnDraw(Surf_Display, SurfBlock,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);//village zu testzwecken
					break; //schleife verlassen nach einer armee
				} else {
					break; //schleife verlassen wenn nicht begehbar
				}
			}

			for (i = 1; i <= ArmySelected->GetStepsLeft(); i++) {
				coordinates coord(ArmySelected->getCoords().x - i,
						ArmySelected->getCoords().y);
				if (map.isWalkable(coord) == true
						and map.isPlace(coord) == false
						and map.isArmyPositioned(coord) == false) { //links lang
					CSurface::OnDraw(Surf_Display, SurfWalkable,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);
				} else if(map.isPlace(coord) == true) {
					CSurface::OnDraw(Surf_Display, SurfPlace,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);
					break; //schleife verlassen nach einem Gebäude
				}else if(map.isArmyPositioned(coord) == true){
					CSurface::OnDraw(Surf_Display, SurfBlock,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);//village zu testzwecken
					break; //schleife verlassen nach einer armee
				} else {
					break; //schleife verlassen wenn nicht begehbar
				}
			}

			for (i = 1; i <= ArmySelected->GetStepsLeft(); i++) {
				coordinates coord(ArmySelected->getCoords().x,
						ArmySelected->getCoords().y - i);
				if (map.isWalkable(coord) == true
						and map.isPlace(coord) == false
						and map.isArmyPositioned(coord) == false) { //hoch
					CSurface::OnDraw(Surf_Display, SurfWalkable,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);
				} else if(map.isPlace(coord) == true) {
					CSurface::OnDraw(Surf_Display, SurfPlace,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);
					break; //schleife verlassen nach einem Gebäude
				}else if(map.isArmyPositioned(coord) == true){
					CSurface::OnDraw(Surf_Display, SurfBlock,
							((coord.x) * TILE_SIZE) - camposx,
							(coord.y * TILE_SIZE) - camposy);//block zu testzwecken
					break; //schleife verlassen nach einer armee
				} else {
					break; //schleife verlassen wenn nicht begehbar
				}
			}

		}
	}

	if (subGS.GET_GameState() == IG_ASSEMBLYPOINT) {
		if (PlaceSelected){
			for(i=0; i < 5;i++){
				for(i2=0; i2 < 5;i2++){
					coordinates coord(PlaceSelected->getCoords().x-2 + i2, PlaceSelected->getCoords().y-2 + i);
					if (map.isWalkable(coord) == true) { //hoch
						CSurface::OnDraw(Surf_Display, SurfWalkable,((coord.x) * TILE_SIZE) - camposx, (coord.y * TILE_SIZE) - camposy);
					}else{
						CSurface::OnDraw(Surf_Display, SurfBlock,((coord.x) * TILE_SIZE) - camposx, (coord.y * TILE_SIZE) - camposy);
					}
				}
			}
		}
	}

	CSurface::OnDraw(Surf_Display, SurfMain,0,0);


	ShowSelected();

	if (subGS.GET_GameState() == IG_ARMYOPTION) {
		if (ArmySelected) {
			CSurface::OnDraw(Surf_Display, SurfArmyOptionBackground,
					ArmySelected->getCoords().x * TILE_SIZE + TILE_SIZE
							- camposx,
					ArmySelected->getCoords().y * TILE_SIZE - camposy);
		}
	}


	if (subGS.GET_GameState() == IG_VILLAGEMENU) {
		CSurface::OnDraw(Surf_Display, SurfVillageMenuBackground, 546, 423);

		//show troops
		if (PlaceSelected) {
			if (PlaceSelected->town_army) {
				for (i = 0; i < PlaceSelected->town_army->units.size();
						i++) {
					char * path =
							new char[PlaceSelected->town_army->units[i]->getImgPath().length()];
					strcpy(path,
							PlaceSelected->town_army->units[i]->getImgPath().c_str());
					SurfSlotOwns = CSurface::OnLoad(path);
					CSurface::OnDraw(Surf_Display, SurfSlotOwns,18 + (i * 40), 405);
				}
			}
		}
	}
}

void GameClient::OnRender() {
	if (GS.GET_GameState() == START_SCREEN) {
		RenderStartScreen();
	}

	if (GS.GET_GameState() == INGAME) {
		RenderInGame();
	}

	SDL_Flip(Surf_Display);
}

