/*
 * EArmy.cpp
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#include "EArmy.h"

EArmy::EArmy() : m_steps_left_in_round(0) {
}

EArmy::~EArmy() {
}

void EArmy::AddUnit(EUnitPtr unit) {
	units.push_back(unit);
}

void EArmy::RemoveUnit(EUnitPtr unit){
	int pos=0;
	for(int i=0;i<units.size();i++){
		if(units[i]==unit){
			pos=i;
		}
	}

	units.erase(units.begin()+pos);
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
