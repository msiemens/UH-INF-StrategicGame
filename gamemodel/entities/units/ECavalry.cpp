/*
 * ECavalry.cpp
 *
 *  Created on: 15.01.2013
 *      Author: Henrik
 */

#include <gamemodel/entities/units/ECavalry.h>

ECavalry::ECavalry() {
	// TODO Auto-generated constructor stub
	atk=(7);
	def=(4);
	mor=(4);
	pac=(10);
	tac=(2);
	amount=30;
	cost_gold = 20;
	cost_stone = 12;
	cost_wood = 15;
	setIconPath("client/gfx/entity/icons/cavalry.png");
}

ECavalry::~ECavalry() {
	// TODO Auto-generated destructor stub
}

