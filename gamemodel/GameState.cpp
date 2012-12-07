/*
 * GameState.cpp
 *
 *  Created on: 22.11.2012
 *      Author: Armend
 */

#include "gamemodel/GameState.h"

using namespace std;

GameState::GameState() {
	// TODO Auto-generated constructor stub
	this->aktivGS = 0;//Startscreen
}

GameState::~GameState() {
	// TODO Auto-generated destructor stub
}

int GameState::GET_GameState(){
	return this->aktivGS;	//get aktiv GameState
}

void GameState::SET_GameState(int GS){
	this->aktivGS = GS;		//set aktiv GameState
}

