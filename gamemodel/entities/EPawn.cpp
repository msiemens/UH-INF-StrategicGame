/*
 * EPawn.cpp
 *
 *  Created on: 20.11.2012
 *      Author: Armend
 */

#include "gamemodel/entities/EPawn.h"

EPawn::EPawn() {
	this->name = "Pawn";
	this->ATK = 5;
	this->DEF = 5;
	this->MOR = 5;
	this->PAC = 5;
	this->amount = 100;
	this->cost = 100;

	// TODO Auto-generated constructor stub

}

EPawn::~EPawn() {
	// TODO Auto-generated destructor stub
}

int EPawn::GET_att(int i){
	switch(i){
		case 1:
			return this->ATK;
			break;
		case 2:
			return this->DEF;
			break;
		case 3:
			return this->PAC;
			break;
		case 4:
			return this->MOR;
			break;

		default:
			return 0;
	}
}

int EPawn::GET_cost(){
	return this->cost;
}
int EPawn::GET_amount(){
	return this->amount;
}
std::string EPawn::GET_name(){
	return this->name;
}
