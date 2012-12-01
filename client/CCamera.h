/*
 * CCamera.h
 *
 *  Created on: 01.12.2012
 *      Author: Armend
 */

#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include <SDL/SDL.h>

#include "client/Define.h"

enum {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class CCamera {
public:
	static CCamera CameraControl;

private:
	int X;
	int Y;

	int* TargetX;
	int* TargetY;

public:
	int TargetMode;

public:
	CCamera();

public:
	void OnMove(int MoveX, int MoveY);

public:
	int GetX();
	int GetY();

public:
	void SetPos(int X, int Y);

	void SetTarget(int* X, int* Y);
};

#endif
