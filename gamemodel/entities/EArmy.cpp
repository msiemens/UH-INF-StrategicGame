/*
 * EArmy.cpp
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#include "EArmy.h"

EArmy::EArmy() : m_steps_left_in_round(0) {
	this->setImgPath("client/gfx/entity/army.png");
}

EArmy::~EArmy() {
}

void EArmy::AddUnit(EUnitPtr unit) {
	if(units.size()<10){
		units.push_back(unit);
	}
}

void EArmy::RemoveUnit(EUnitPtr unit) {
	int counter=0;
	for(auto u:units){
		if(u==unit){
			units.erase(units.begin()+counter);
			break;
		}
		else{
			counter++;
		}
	}
}

int EArmy::GetStepsLeft() {
	return m_steps_left_in_round;
}

void EArmy::SetStepsLeft(int steps) {
	m_steps_left_in_round = steps;
}

void EArmy::Move(int dir, int size) {
	if (size <= m_steps_left_in_round) {
		switch (dir) {
		case 0:
			setCoords(getCoords().x, getCoords().y - size);
			break;
		case 1:
			setCoords(getCoords().x + size, getCoords().y);
			break;
		case 2:
			setCoords(getCoords().x, getCoords().y + size);
			break;
		case 3:
			setCoords(getCoords().x - size, getCoords().y);
			break;
		}

		m_steps_left_in_round -= size;
	}
}

int EArmy::GetAtk() {
	int atk_ges=0;
	for(auto unit:units){
		atk_ges+=unit->GetAtk();
	}
	return atk_ges;
}

int EArmy::GetDef() {
	int def_ges=0;
	for(auto unit:units){
		def_ges+=unit->GetDef();
	}
	return def_ges;
}

int EArmy::GetMor() {
	int mor_avg=0;
	for(auto unit:units){
		mor_avg+=unit->GetDef();
	}

	mor_avg=mor_avg/units.size();

	return mor_avg;
}

int EArmy::GetPac() {
	int pac=100;
	for(auto unit:units){
		pac=(unit->GetPac()<pac)?unit->GetPac():pac;
	}
	return pac;
}

int EArmy::GetTac() {
	int tac_avg=0;
	for(auto unit:units){
		tac_avg+=unit->GetMor();
	}

	tac_avg=tac_avg/units.size();
	return tac_avg;
}
