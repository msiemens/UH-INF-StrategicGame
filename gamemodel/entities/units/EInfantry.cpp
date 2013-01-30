/*
 * EInfantry.cpp
 *
 *  Created on: 15.01.2013
 *      Author: Henrik
 */

#include "gamemodel/entities/units/EInfantry.h"

EInfantry::EInfantry() {
	// TODO Auto-generated constructor stub
	atk=(3);
	def=(3);
	mor=(2);
	pac=(2);
	tac=(4);
	amount=40;
	cost_gold = 20;
	cost_stone = 5;
	cost_wood = 7;
	setIconPath("client/gfx/entity/icons/infantry.png");

}

EInfantry::~EInfantry() {
	// TODO Auto-generated destructor stub
}

