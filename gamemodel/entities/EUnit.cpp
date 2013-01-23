/*
 * ETroops.cpp
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#include "EUnit.h"

EUnit::EUnit(): GameEntity() , amount(67){
	setImgPath("client/gfx/entity/army.png");
	setIconPath("client/gfx/entity/icons/army.png");
}

EUnit::~EUnit() {
}

int EUnit::GetAtk(){
	return atk;
}

int EUnit::GetDef() {
	return def;
}

int EUnit::GetMor() {
	return mor;
}

int EUnit::GetPac() {
	return pac;
}

int EUnit::GetTac() {
	return tac;
}

int EUnit::GetAmount() {
	return amount;
}

void EUnit::SetAmount(int amount) {
	this->amount=amount;
}

void EUnit::SetDamagePoints(int damage) {
	SetAmount(GetAmount()-damage);
}
