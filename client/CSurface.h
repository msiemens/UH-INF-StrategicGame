/*
 * CSurface.h
 *
 *  Created on: 23.11.2012
 *      Author: Armend
 */

#include <SDL/SDL.h>
#include <string>

#ifndef CSURFACE_H_
#define CSURFACE_H_

using namespace std;

class CSurface {
public:
	CSurface();
	virtual ~CSurface();
	string GetImgPath();
	void SetImgPath(string path);

public:
    static SDL_Surface* OnLoad(char* File);
    string pathtoimg;
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);
    static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);
};

#endif /* CSURFACE_H_ */
