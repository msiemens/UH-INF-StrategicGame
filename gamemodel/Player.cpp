/*
 * Player.cpp
 *
 *  Created on: 09.11.2012
 *      Author: markus
 */

#include <typeinfo>
#include <iostream>

#include "Player.h"
#include "gamemodel/entities/EArmy.h"
#include "gamemodel/entities/EPlace.h"

using namespace std;

Player::Player(int id) :
		playerId(id) {
}

Player::~Player() {
}

int Player::getPlayerId() {
	return playerId;
}

void Player::addArmy(EArmy army) {
	armies.insert(armies.end(), army);
}

void Player::addPlace(EPlace place) {
	places.insert(places.end(), place);
}

void Player::addTroops(ETroops troops) {

}

void Player::addRessource(GameRessource ressource) {

}

int Player::getRessourceCount(GameRessource ressource) {
	return 0;
}

