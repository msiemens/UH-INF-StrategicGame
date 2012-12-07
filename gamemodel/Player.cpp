/*
 * Player.cpp
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#include "Player.h"
#include "gamemodel/entities/EArmy.h"
#include "gamemodel/entities/EPlace.h"

using namespace std;

Player::Player(int id){
	playerid=id;
}

int Player::getPlayerId(){
	return playerid;
}

void Player::addArmy(EArmy army){
	armies.insert(armies.begin(),army);
}

void Player::addPlace(EPlace place){
	places.insert(places.begin(),place);
}


