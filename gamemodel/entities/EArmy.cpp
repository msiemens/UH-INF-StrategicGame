/*
 * EArmy.cpp
 *
 *  Created on: 30.11.2012
 *      Author: Henrik
 */

#include "gamemodel/entities/EArmy.h"
#include "gamemodel/entities/ETroops.h"

namespace std {

EArmy::EArmy() {
	// TODO Auto-generated constructor stub
	atk=0;
	def=0;
	pac=0;
	mor=0;
	tac=0;
}

EArmy::~EArmy() {
	// TODO Auto-generated destructor stub
}

void EArmy::setPosition(int x,int y){
	position.x=x;
	position.y=y;
}

void EArmy::addTroop(ETroops troop,int slot){
	troops[slot]=troop;
}

void EArmy::setAtk(){
	for(ETroops t:troops){
		if(t!=0){
			atk+=t.ATK;
		}
	}
}

void EArmy::setDef(){
	for(ETroops t:troops){
		if(t!=0){
			def+=t.DEF;
		}
	}
}

void EArmy::setPac(){
	for(ETroops t:troops){
		if(t!=0){
			pac=(t.PAC<pac)?t.PAC:pac;
		}
	}
}

void EArmy::setMor(){
	for(ETroops t:troops){
		if(t!=0){
			mor+=t.MOR;
		}
	}
}

void EArmy::setTac(){
	int enttac;
	int counter=0;
	for(ETroops t:troops){
		if(t!=0){
			enttac+=t.TAC;
			counter++;
		}
	}

	tac=enttac/counter;
}

int EArmy::getAtk(){
	return atk;
}

int EArmy::getDef(){
	return def;
}

int EArmy::getPac(){
	return pac;
}

int EArmy::getMor(){
	return mor;
}

int EArmy::getTac(){
	return tac;
}

} /* namespace std */
