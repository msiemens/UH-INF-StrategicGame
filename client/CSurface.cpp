/*
 * CSurface.cpp
 *
 *  Created on: 23.11.2012
 *      Author: Armend
 */

#include "CSurface.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>

using namespace std;

CSurface::CSurface() {
	// TODO Auto-generated constructor stub

}

CSurface::~CSurface() {
	// TODO Auto-generated destructor stub
}

SDL_Surface* CSurface::OnLoad(char* File) {
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if((Surf_Temp = IMG_Load(File)) == NULL) {
    	cerr << "File not found: " << File << endl;
        return NULL;
    }

    Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);
    return Surf_Return;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X,
		int Y) {
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	Surf_Src->clip_rect.x = X;
	Surf_Src->clip_rect.y = Y;


	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

	return true;
}

bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X,
		int Y, int X2, int Y2, int W, int H) {
	if (Surf_Dest == NULL || Surf_Src == NULL) {
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;

	SrcR.x = X2;
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

	return true;
}

void CSurface::SetImgPath(string path){
	this->pathtoimg = path;
}

string CSurface::GetImgPath(){
	return this->pathtoimg;
}
