/*
 * EPawn.cpp
 *
 *  Created on: 15.01.2013
 *      Author: Henrik
 */

#include "gamemodel/entities/units/EPawn.h"

EPawn::EPawn(){
	// TODO Auto-generated constructor stub
	atk=(1);
	def=(1);
	mor=(1);
	tac=(1);
	pac=(1);
	amount=60;
	cost_gold = 10;
	cost_stone = 0;
	cost_wood = 2;
	setIconPath("client/gfx/entity/icons/pawn.png");
}

EPawn::~EPawn() {
	// TODO Auto-generated destructor stub
}

