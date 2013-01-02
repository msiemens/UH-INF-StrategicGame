/*
 * EArmy.cpp
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#include <iostream>

#include <gamemodel/entities/EArmy.h>
#include <gamemodel/entities/ETroops.h>
#include <gamemodel/utils/coordinates.h>

EArmy::EArmy() {
	// TODO Auto-generated constructor stub
	atk = 0;
	def = 0;
	pac = 0;
	mor = 0;
	tac = 0;
	steps = 0;
}

EArmy::~EArmy() {
	// TODO Auto-generated destructor stub
}

void EArmy::Move(int dir, int size){
	if(size <= getSteps()){
		switch(dir){
			case 0:
				setCoords(getCoords().x, getCoords().y - size);
				setStep(getSteps() - size);
				break;
			case 1:
				setCoords(getCoords().x + size, getCoords().y);
				setStep(getSteps() - size);
				break;
			case 2:
				setCoords(getCoords().x, getCoords().y + size);
				setStep(getSteps() - size);
				break;
			case 3:
				setCoords(getCoords().x - size, getCoords().y);
				setStep(getSteps() - size);
				break;
		}
	}else{

	}
}

void EArmy::addTroop(ETroopsPtr troop) {
	int troop_count=troops.size();
	if(troop_count<11){
		troops.insert(troops.begin(),troop);
	}
}

void EArmy::setAtk() {
}

void EArmy::setDef() {
	/* for (ETroops t : troops) {
		if (t != 0) {
			def += t.DEF;
		}
	}*/
}

void EArmy::setPac(int x) {
	pac = x;
//	for (ETroops t : troops) {
//		if (t != 0) {
//			pac = (t.PAC < pac) ? t.PAC : pac;
//		}
//	}
}

void EArmy::setMor() {
//	for (ETroops t : troops) {
//		if (t != 0) {
//			mor += t.MOR;
//		}
//	}
}

void EArmy::setTac() {
	int enttac;
	int counter = 0;
//	for (ETroops t : troops) {
//		if (t != 0) {
//			enttac += t.TAC;
//			counter++;
//		}
//	}

	tac = enttac / counter;
}


void EArmy::setStep(int x) {
	steps = x;
}
int EArmy::getSteps() {
	return steps;
}
int EArmy::getAtk() {
	return atk;
}

int EArmy::getDef() {
	return def;
}

int EArmy::getPac() {
	return pac;
}

int EArmy::getMor() {
	return mor;
}

int EArmy::getTac() {
	return tac;
}
